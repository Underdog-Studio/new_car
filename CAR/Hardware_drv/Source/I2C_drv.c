#include "I2C_drv.h"

static void I2C_GPIO_Config(void)
{
	rcu_periph_clock_enable(RCU_GPIOB);

	rcu_periph_clock_enable(RCU_I2C0);
	gpio_init(GPIOB, GPIO_MODE_AF_OD, GPIO_OSPEED_50MHZ, GPIO_PIN_8);
	gpio_init(GPIOB, GPIO_MODE_AF_OD, GPIO_OSPEED_50MHZ, GPIO_PIN_9);
	gpio_pin_remap_config(GPIO_I2C0_REMAP,ENABLE);
}

static void I2C_Config(void)
{
	i2c_clock_config(I2C0, I2C_Speed, I2C_DTCY_2);
	i2c_mode_addr_config(I2C0, I2C_I2CMODE_ENABLE, I2C_ADDFORMAT_7BITS, 0x72);
	i2c_enable(I2C0);
	i2c_ack_config(I2C0, I2C_ACK_ENABLE);
}

void I2C_Init(void)
{
	I2C_GPIO_Config();
	I2C_Config();
}

uint8_t I2C_Register_Write_1Byte(uint8_t Device_address,uint8_t Register_address,uint8_t data)
{
	taskENTER_CRITICAL();
	while(i2c_flag_get(I2C0, I2C_FLAG_I2CBSY));
	i2c_start_on_bus(I2C0);
	while(!i2c_flag_get(I2C0, I2C_FLAG_SBSEND));
	
	i2c_master_addressing(I2C0, Device_address, I2C_TRANSMITTER);
	while(!i2c_flag_get(I2C0, I2C_FLAG_ADDSEND));
	i2c_flag_clear(I2C0,I2C_FLAG_ADDSEND);
	
	while(!i2c_flag_get(I2C0, I2C_FLAG_TBE));
	i2c_data_transmit(I2C0, Register_address);
	
	while(!i2c_flag_get(I2C0, I2C_FLAG_TBE)){};
  i2c_data_transmit(I2C0, data);
	
	while(!i2c_flag_get(I2C0, I2C_FLAG_TBE));
	i2c_stop_on_bus(I2C0);
	while(I2C_CTL0(I2C0)&0x0200);
		
 taskEXIT_CRITICAL();	
	return 1;
}

uint8_t I2C_Register_Read_1Byte(uint8_t Device_address,uint8_t Register_address,uint8_t *data)
{
	taskENTER_CRITICAL();
	while(i2c_flag_get(I2C0, I2C_FLAG_I2CBSY));
	i2c_start_on_bus(I2C0);
	while(!i2c_flag_get(I2C0, I2C_FLAG_SBSEND));
	
	i2c_master_addressing(I2C0, Device_address, I2C_TRANSMITTER);
	while(!i2c_flag_get(I2C0, I2C_FLAG_ADDSEND));
	i2c_flag_clear(I2C0, I2C_FLAG_ADDSEND);
	
	while(!i2c_flag_get(I2C0, I2C_FLAG_TBE));

	i2c_data_transmit(I2C0,Register_address);
	while(!i2c_flag_get(I2C0, I2C_FLAG_TBE));
	
	i2c_start_on_bus(I2C0);
	while(!i2c_flag_get(I2C0, I2C_FLAG_SBSEND));
	
	i2c_master_addressing(I2C0, Device_address, I2C_RECEIVER);
	while(!i2c_flag_get(I2C0, I2C_FLAG_ADDSEND));
	i2c_flag_clear(I2C0, I2C_FLAG_ADDSEND);
	
	i2c_ack_config(I2C0, I2C_ACK_DISABLE);			

  i2c_stop_on_bus(I2C0);							
  while(!i2c_flag_get(I2C0, I2C_FLAG_RBNE));		
  *data  = i2c_data_receive(I2C0);			
	i2c_ack_config(I2C0, I2C_ACK_ENABLE);			
	taskEXIT_CRITICAL();	
	return 1;
}

uint8_t I2C_Register_Read_nByte(uint8_t Device_address,uint8_t Register_address,uint8_t *data,uint8_t num)
{
	uint8_t i=0;
	taskENTER_CRITICAL();
	while(i2c_flag_get(I2C0, I2C_FLAG_I2CBSY));
	i2c_start_on_bus(I2C0);
	while(!i2c_flag_get(I2C0, I2C_FLAG_SBSEND));
	
	i2c_master_addressing(I2C0, Device_address, I2C_TRANSMITTER);
	while(!i2c_flag_get(I2C0, I2C_FLAG_ADDSEND));
	i2c_flag_clear(I2C0, I2C_FLAG_ADDSEND);
	
	while(!i2c_flag_get(I2C0, I2C_FLAG_TBE));

	i2c_data_transmit(I2C0,Register_address);
	while(!i2c_flag_get(I2C0, I2C_FLAG_TBE));
	
	i2c_start_on_bus(I2C0);
	while(!i2c_flag_get(I2C0, I2C_FLAG_SBSEND));
	
	i2c_master_addressing(I2C0, Device_address, I2C_RECEIVER);
	while(!i2c_flag_get(I2C0, I2C_FLAG_ADDSEND));
	i2c_flag_clear(I2C0, I2C_FLAG_ADDSEND);

	while(num>1&&i<(num-1))
	{
		while(!i2c_flag_get(I2C0, I2C_FLAG_RBNE));		
		data[i++] = i2c_data_receive(I2C0);			
	}
	
	i2c_ack_config(I2C0, I2C_ACK_DISABLE);			
	
	i2c_stop_on_bus(I2C0);							
	while(!i2c_flag_get(I2C0, I2C_FLAG_RBNE));		
	data[i]  = i2c_data_receive(I2C0);			
	i2c_ack_config(I2C0, I2C_ACK_ENABLE);			
	taskEXIT_CRITICAL();	
	return 1;
}

uint8_t I2C_ID[127];
void I2C0_Scan(void)
{
	uint8_t Count=0,count1;
	uint16_t TTTT=0;
	taskENTER_CRITICAL();
	//i2c_stop_on_bus(I2C0);
	while((Count++)<255)
	{
		while(i2c_flag_get(I2C0, I2C_FLAG_I2CBSY));
		i2c_start_on_bus(I2C0);
		while(!i2c_flag_get(I2C0, I2C_FLAG_SBSEND));
		
		i2c_master_addressing(I2C0, Count, I2C_RECEIVER);
			
		while(1)
		{
			if(i2c_flag_get(I2C0, I2C_FLAG_ADDSEND))
			{
				I2C_ID[count1++] = Count;
				i2c_flag_clear(I2C0, I2C_FLAG_ADDSEND);
				i2c_stop_on_bus(I2C0);
				break;
			}
			if(TTTT++>5000)
			{
				i2c_flag_clear(I2C0, I2C_FLAG_ADDSEND);
				i2c_stop_on_bus(I2C0);
				TTTT=0;
				break;
			}
		}
	}
	taskEXIT_CRITICAL();	
}




