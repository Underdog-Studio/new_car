#ifndef __Execute_System_H
#define __Execute_System_H

#include "Control_System.h"
#include "Motor_Control.h"
#include "System_Time.h"

#include "arm_math.h"
#include "Servo.h"


void Execute_System_Init(void);
uint8_t Set_Move(uint8_t n,int16_t h,int16_t Vel,int16_t acc);
void Execute_System(void);


int16_t Get_X_Body_Vel(void);
int16_t Get_Y_Body_Vel(void);
int16_t Get_Yaw_Body_Vel(void);
uint8_t Get_X_State(void);
uint8_t Get_Y_State(void);
uint8_t Get_Yaw_State(void);

#endif

