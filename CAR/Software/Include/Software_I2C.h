#ifndef __Software_I2C_H
#define __Software_I2C_H

#include "gd32f30x.h"
#include "gpio_drv.h"

#include "FreeRTOS.h"
#include "task.h"


typedef struct
{
	gpio_control SCL;
	gpio_control SDA;
	int Baud_Rate;
}Sim_I2C;//��������I2C��ṹ����


void IIC_Start(Sim_I2C I2C);
void IIC_Stop(Sim_I2C I2C);
uint8_t IIC_Wait_Ack(Sim_I2C I2C);
void IIC_Ack(Sim_I2C I2C);
void IIC_NAck(Sim_I2C I2C);
void IIC_Send_Byte(Sim_I2C I2C,uint8_t Data);
uint8_t IIC_Read_Byte(Sim_I2C I2C,uint8_t ack);

//I2C�����ʼ�����
void Software_I2C_Init(void);
//I2Cдһ������ֽ���
uint8_t Sensor_Write_Byte(Sim_I2C I2C,uint8_t Device_ADDR,uint8_t Reg_ADDR,uint8_t DATA);
//I2C����һ�����ֽ���
uint8_t Sensor_Read_Byte(Sim_I2C I2C,uint8_t Device_ADDR,uint8_t Reg_ADDR);
//I2C��������
uint8_t Sensor_Read_Len(Sim_I2C I2C,uint8_t addr,uint8_t reg,uint8_t len,uint8_t *buf);
//����ȡ���������I2C
Sim_I2C GET_SofI2C(uint8_t num);

#endif

