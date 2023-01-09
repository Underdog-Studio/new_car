
#include "ws2812_drv.h"



const ws2812_byte ws2812 =
{
		ws2812_Init
};



void ws2812_spi_init(void)
{
	spi_parameter_struct spi_init_struct;
	rcu_periph_clock_enable(RCU_SPI1);
	rcu_periph_clock_enable(RCU_GPIOB);
	gpio_init(GPIOB, GPIO_MODE_AF_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_15);
	spi_i2s_deinit(SPI1);
	spi_struct_para_init(&spi_init_struct);
	spi_init_struct.trans_mode = SPI_TRANSMODE_BDTRANSMIT;
	spi_init_struct.device_mode = SPI_MASTER;
	spi_init_struct.frame_size = SPI_FRAMESIZE_16BIT;
	spi_init_struct.clock_polarity_phase = SPI_CK_PL_HIGH_PH_1EDGE;
	spi_init_struct.nss = SPI_NSS_SOFT;
	spi_init_struct.prescale = SPI_PSC_4;
	spi_init_struct.endian = SPI_ENDIAN_MSB;
	spi_init(SPI1,&spi_init_struct);

	
	spi_enable(SPI1);
}

static void spi_Send_byte(uint16_t data)
{
	while(spi_i2s_flag_get(SPI1,SPI_FLAG_TBE)==RESET);
	spi_i2s_data_transmit(SPI1,data);
}

void ws2812_Init(void)
{
	ws2812_spi_init();
}


uint16_t ws2812_code[24];
void ws2812_Control(uint8_t R,uint8_t G,uint8_t B)
{
	uint8_t i;
	for(i=0;i<8;i++)
	{
		if(((G<<i)&0x80)==0x80)
			ws2812_code[i]=Code1;
		else
			ws2812_code[i]=Code0;
	}
	for(i=0;i<8;i++)
	{
		if(((R<<i)&0x80)==0x80)
			ws2812_code[i+8]=Code1;
		else
			ws2812_code[i+8]=Code0;
	}
	for(i=0;i<8;i++)
	{
		if(((B<<i)&0x80)==0x80)
			ws2812_code[i+16]=Code1;
		else
			ws2812_code[i+16]=Code0;
	}
  for(i=0;i<CodeR;i++)
		spi_Send_byte(0xFFFF);
	for(i=0;i<24;i++)
	{
		spi_Send_byte(ws2812_code[i]);
	}

}







