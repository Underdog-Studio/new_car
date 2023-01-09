#ifndef __Control_System_H
#define __Control_System_H

#include "Motor_Control.h"
#include "Solution_System.h"
#include "PID.h"
#include "Button.h"

#include "Task_Priority.h"
#include "semphr.h"
//�������
void Control_System_Init(void);
//������3��
void Set_Motor_Target_Vel(uint8_t Mn,float Vel);
//��2����3��
float Get_Motor_Target_Vel(uint8_t Mn);
//����3��
float Get_Motor_Observation_Vel(uint8_t Mn);
//��2��3��
void Set_Body_X(float Vel);
void Set_Body_Y(float Vel);
void Set_Body_Yaw(float Vel);
float Get_Body_X(void);
float Get_Body_Y(void);
float Get_Body_Yaw(void);
	
void Set_Yaw_PID(PID_Type PID_Temp);

void Control_System_Enable(void);
void Control_System_Disable(void);
uint8_t Get_Control_Switch(void);



#endif



