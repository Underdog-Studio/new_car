#ifndef _EEPROM_H
#define _EEPROM_H

#include "gd32f30x.h"
//#include "i2c_drv.h"
#include "System_time.h"
#include "FreeRTOS.h"
#include "task.h"
#include "Flash_drv.h"

#define EEPROM_ADDR 0XA0

void EEPROM_Init(void);

uint8_t Parameters_Loading(void);//�������������


//�������ȸ��������ݲ����
float EEPROM_Read_float(uint16_t ReadAddr);
void EEPROM_Write_float(uint16_t ReadAddr,float data);

//�������ݲ����
uint32_t EEPROM_ReadOneWord(uint16_t ReadAddr);
void EEPROM_WriteOneWord(uint16_t WriteAddr,uint32_t data);

//���������ݲ���
uint16_t EEPROM_ReadOneHalfword(uint16_t ReadAddr);
void EEPROM_WriteOneHalfword(uint16_t WriteAddr,uint16_t data);

//�ֽ����ݲ����
void EEPROM_WriteOneByte(uint8_t WriteAddr,uint8_t data);
uint8_t EEPROM_ReadOneByte(uint16_t ReadAddr);

void EEPROM_Updata(void);
void EEPROM_Data_Save(void);


#endif

