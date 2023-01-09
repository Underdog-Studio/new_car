#ifndef __I2C_drv_H
#define __I2C_drv_H

#include "gd32f30x.h"
#include "FreeRTOS.h"
#include "task.h"


#define I2C_Speed 350000


void I2C_Init(void);

uint8_t I2C_Register_Write_1Byte(uint8_t Device_address,uint8_t Register_address,uint8_t data);
uint8_t I2C_Register_Read_1Byte(uint8_t Device_address,uint8_t Register_address,uint8_t *data);
uint8_t I2C_Register_Read_nByte(uint8_t Device_address,uint8_t Register_address,uint8_t *data,uint8_t num);

void I2C0_Scan(void);
#endif




