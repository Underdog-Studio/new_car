#include "Software_I2C.h"

void _nop_(uint8_t i)
{
	while(i--);
}

Sim_I2C Sof_I2C1,Sof_I2C2;


void Software_I2C_Init(void)
{
	Sof_I2C1.SCL = get_gpio_struct(4);
	Sof_I2C1.SCL.GPIO_HIGH();
	Sof_I2C1.SDA = get_gpio_struct(5);
	Sof_I2C1.SDA.GPIO_HIGH();
}

Sim_I2C GET_SofI2C(uint8_t num)
{
	switch(num)
	{
		case 1:
			return Sof_I2C1;
		case 2:
			return Sof_I2C2;
	}
}



void IIC_Start(Sim_I2C I2C)
{
	I2C.SDA.GPIO_MODE(1);     
	I2C.SDA.GPIO_HIGH();
	I2C.SCL.GPIO_HIGH();
	_nop_(3);
	I2C.SDA.GPIO_LOW();
	_nop_(3);
	I2C.SCL.GPIO_LOW();
}

void IIC_Stop(Sim_I2C I2C)
{
	I2C.SDA.GPIO_MODE(1);     
	I2C.SCL.GPIO_LOW();
	I2C.SDA.GPIO_LOW();
	_nop_(3);
	I2C.SCL.GPIO_HIGH();
	I2C.SDA.GPIO_HIGH();
	_nop_(3);
}

uint8_t IIC_Wait_Ack(Sim_I2C I2C)
{
	uint8_t ucErrTime1=0;
	I2C.SDA.GPIO_MODE(0);     
	I2C.SDA.GPIO_HIGH();
	_nop_(3);//3
  I2C.SCL.GPIO_HIGH();
	_nop_(3);
	
	while(I2C.SDA.GPIO_GET())
	{
		if(ucErrTime1++>=10)
		{
			IIC_Stop(I2C);
			return 1;
		}
	}
	I2C.SCL.GPIO_LOW();
	return 0;
}

void IIC_Ack(Sim_I2C I2C)
{
	I2C.SCL.GPIO_LOW();
	I2C.SDA.GPIO_MODE(1);     
	I2C.SDA.GPIO_LOW();
	_nop_(3);
	I2C.SCL.GPIO_HIGH();
	_nop_(3);
	I2C.SCL.GPIO_LOW();
}


void IIC_NAck(Sim_I2C I2C)
{
	I2C.SCL.GPIO_LOW();
	I2C.SDA.GPIO_MODE(1);     
	I2C.SDA.GPIO_HIGH();
	_nop_(3);
	I2C.SCL.GPIO_HIGH();
	_nop_(3);
	I2C.SCL.GPIO_LOW();
}


void IIC_Send_Byte(Sim_I2C I2C,uint8_t Data)
{
	uint8_t t;
	I2C.SDA.GPIO_MODE(1);     
	I2C.SCL.GPIO_LOW();
	for(t=0;t<8;t++)
	{
		if((Data&0x80)>>7)
			I2C.SDA.GPIO_HIGH();
		else I2C.SDA.GPIO_LOW();
		Data<<=1;
		I2C.SCL.GPIO_HIGH();
		_nop_(3);
		I2C.SCL.GPIO_LOW();
		_nop_(3);
	}
}	

uint8_t IIC_Read_Byte(Sim_I2C I2C,uint8_t ack)
{
	uint8_t i,receive1=0;
	I2C.SDA.GPIO_MODE(0);     
	for(i=0;i<8;i++ )
	{
		I2C.SCL.GPIO_LOW();
		_nop_(3);
		I2C.SCL.GPIO_LOW();
		receive1<<=1;
		if(I2C.SDA.GPIO_GET())receive1++;   
		_nop_(3);
	}
	if (!ack)
		IIC_NAck(I2C);
	else
		IIC_Ack(I2C); 
	return receive1;	
}


uint8_t Sensor_Write_Byte(Sim_I2C I2C,uint8_t Device_ADDR,uint8_t Reg_ADDR,uint8_t DATA) 				 
{ 
	taskENTER_CRITICAL();
	IIC_Start(I2C); 
	IIC_Send_Byte(I2C,(Device_ADDR<<1)|0);
	if(IIC_Wait_Ack(I2C))	
	{
		IIC_Stop(I2C);	
		taskEXIT_CRITICAL();		
		return 0;		
	}
  IIC_Send_Byte(I2C,Reg_ADDR);	
  IIC_Wait_Ack(I2C);		
	IIC_Send_Byte(I2C,DATA);
	if(IIC_Wait_Ack(I2C))	
	{
		IIC_Stop(I2C);	 
		taskEXIT_CRITICAL();
		return 0;		 
	}		 
  IIC_Stop(I2C);	
	taskEXIT_CRITICAL();	
	return 1;
}


uint8_t Sensor_Read_Byte(Sim_I2C I2C,uint8_t Device_ADDR,uint8_t Reg_ADDR)
{
	uint8_t res;
	taskENTER_CRITICAL();
  IIC_Start(I2C); 
	IIC_Send_Byte(I2C,(Device_ADDR<<1)|0);
	IIC_Wait_Ack(I2C);		
  IIC_Send_Byte(I2C,Reg_ADDR);	
  IIC_Wait_Ack(I2C);		
  IIC_Start(I2C);
	IIC_Send_Byte(I2C,(Device_ADDR<<1)|1);
  IIC_Wait_Ack(I2C);		
	res=IIC_Read_Byte(I2C,0);
  IIC_Stop(I2C);			
	taskEXIT_CRITICAL();	
	return res;		
}



uint8_t Sensor_Read_Len(Sim_I2C I2C,uint8_t addr,uint8_t reg,uint8_t len,uint8_t *buf)
{ 
	taskENTER_CRITICAL();
 	IIC_Start(I2C); 
	IIC_Send_Byte(I2C,(addr<<1)|0);
	if(IIC_Wait_Ack(I2C))	
	{
		IIC_Stop(I2C);		
		taskEXIT_CRITICAL();	
		return 0;		
	}
  IIC_Send_Byte(I2C,reg);	
  IIC_Wait_Ack(I2C);		
  IIC_Start(I2C);
	IIC_Send_Byte(I2C,(addr<<1)|1);	
  IIC_Wait_Ack(I2C);		
	while(len)
	{
		if(len==1)*buf=IIC_Read_Byte(I2C,0);
		else *buf=IIC_Read_Byte(I2C,1);		 
		len--;
		buf++; 
	}    
  IIC_Stop(I2C);	 
	taskEXIT_CRITICAL();	
	return 1;	
}


