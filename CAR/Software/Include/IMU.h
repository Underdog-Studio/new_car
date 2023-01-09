#ifndef __IMU_H
#define __IMU_H

#include "I2C_drv.h"
#include "System_time.h"
#include "ws2812_drv.h"
#include "BUZZER.h"

#include "My_Math.h"

typedef struct
{
	float x;
	float y;
	float z;
}Three_axes;//����������������

void IMU_Init(void);

//���������������ַ
#define ICM_ADDR 0xD2//0X69  0xd1
#define IST_ADDR 0x1A//0x0D 0x1A



//���ȡ������ٶ�
uint8_t ICM_Get_Gyroscope(Three_axes *Gyr);
//���ȡ�����ٶ�
uint8_t ICM_Get_Accelerometer(Three_axes *Acc);
//����ȡ��ش�
uint8_t IST_Get_Geomagnetism(Three_axes *Mag);
//���ȡICM20602 ID
uint8_t Get_ICM20602_ID(void);
//����ȡIMU״̬
uint8_t Get_IMU_Status(void);
	
#endif
