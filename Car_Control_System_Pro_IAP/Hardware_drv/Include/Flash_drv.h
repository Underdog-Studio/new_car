#ifndef __Flash_drv_H
#define __Flash_drv_H
#include "gd32f30x_fmc.h"

//GD32F303RCT6
#define PAGE_SIZE           (0x800)//һ��falsh��������С
#define Flash_SIZE          (0x40000)


//flash����
uint8_t Flash_Erase(uint32_t First_address,uint32_t size);
//flashд
uint8_t Flash_Write(uint32_t Write_address,uint8_t *data,uint16_t Write_num);

//Flash��
void Flash_Read(uint32_t Read_address,uint8_t *data,uint16_t Read_num);











#endif

