/**************************
*Description :��������վͨѶ
*Author      :18�����Ի���
*Date        :2021/05/05
*Function    :�ṩ��������λ��ͨѶ�ӿ�
						 
**************************/
#ifndef __ANO_TC_H
#define __ANO_TC_H

#include "gd32f30x.h"
#include "usart_drv.h"
#include "Motor_Control.h"
#include "Solution_System.h"
#include "Control_System.h"
#include "EEPROM.h"


#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "Task_priority.h"
#include "parameter_Loading.h"

//���͸���λ��
#define ANO_Attitude   (0x01) 
#define ANO_Sensors		 (0x02)
#define ANO_Control    (0x03)			
#define ANO_USER_1     (0xF1)

#define ANO_ACK (0xef)



#define ANO_PID1 (0x10)
#define ANO_PID2 (0x11)
#define ANO_PID3 (0x12)
#define ANO_PID4 (0x13)
#define ANO_PID5 (0x14)
#define ANO_PID6 (0x15)

#define ANO_CMD1 (0x01)
#define ANO_CMD2 (0x02)

typedef struct
{
	float ROL;//�����
	float PIT;//������
	float YAW;//ƫ����
	float ALT_USE;//�߶�
	uint8_t FLY_MODEL;//����ģʽ
	uint8_t ARMED;//0���� 1����
}ANO_Attitude_Type;//��̬��Ϣ

typedef struct
{
	float ACC_X;
	float ACC_Y;
	float ACC_Z;
	float GYR_X;
	float GYR_Y;
	float GYR_Z;
	float MAG_X;
	float MAG_Y;
	float MAG_Z;
}ANO_Sensors_Type;//����������

typedef struct
{
	int16_t THR;
	int16_t YAW;
	int16_t ROL;
	int16_t PIT;
	int16_t AUX1;
	int16_t AUX2;
	int16_t AUX3;
	int16_t AUX4;
	int16_t AUX5;
	int16_t AUX6;
}ANO_Control_Type;//���յ��Ŀ�������

typedef struct
{
	int16_t PID1_P;
	int16_t PID1_I;
	int16_t PID1_D;
	int16_t PID2_P;
	int16_t PID2_I;
	int16_t PID2_D;
	int16_t PID3_P;
	int16_t PID3_I;
	int16_t PID3_D;
}ANO_PID_Type;//PID����

typedef struct
{
	float M1_Speed;
	float M2_Speed;
	float M3_Speed;
	float M4_Speed;
	float M1_PID_OUT;
	float M2_PID_OUT;
	float M3_PID_OUT;
	float M4_PID_OUT;
	float M1_PID_Expectations;
	float M2_PID_Expectations;
	float M3_PID_Expectations;
	float M4_PID_Expectations;
	uint16_t Voltage_ADC;
	uint16_t Sever1_ADC;
	uint16_t Sever2_ADC;
	uint16_t Sever3_ADC;
	uint16_t Sever4_ADC;
}ANO_User1_Type;//�û��Զ�������

//��������վ��ʼ��
void ANO_Init(void);
//��������վ�ϴ�����
void ANO_Uploading_data(uint8_t type,void *data);
//��������վ���ݽ���
uint8_t ANO_Receive_data(uint8_t data);
#endif

