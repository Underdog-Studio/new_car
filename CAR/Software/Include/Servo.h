#ifndef __Servo_H
#define __Servo_H

#include "pwm_drv.h"

#define Servo_Max_Angle 270
#define Servo_Max_T     2.4f
#define Servo_Min_T     0.6f

void Servo_Init(void);
float Servo_Pos_Solution(float adc_Value);
void Servo_Pos_Control(uint8_t Sn,float Servo_Target_Pos);


#endif

