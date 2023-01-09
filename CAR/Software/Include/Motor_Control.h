#ifndef __Motor_Control_H
#define __Motor_Control_H


#include "pwm_drv.h"
#include "PID.h"
#include "gpio_drv.h"
#include "EEPROM.h"
#include "Filter.h"

#define M1 1
#define M2 2
#define M3 3
#define M4 4

#define M1_DIR_Periph GPIOB
#define M1_DIR_Pin    GPIO_PIN_12

#define M2_DIR_Periph GPIOB
#define M2_DIR_Pin    GPIO_PIN_13

#define M3_DIR_Periph GPIOB
#define M3_DIR_Pin    GPIO_PIN_14

#define M4_DIR_Periph GPIOA
#define M4_DIR_Pin    GPIO_PIN_12

void Motor_Control_Init(void);

//�?�机?速�?���?�制?(PID)
void Motor_Velocity_Control(uint8_t Mn,float Observed_Vel,float Target_Vel);
//设�?��?输�?��?�?�机?PWM
void Set_Motor_Pwm(uint8_t Mn,float Duty);
//�?��?���?�机P?ID�?��?��
void Set_Motor_PID(uint8_t Mn,PID_Type PID_Temp);
//�?�取?电�?��PID�?�数
PID_Type Get_Motor_PID(uint8_t Mn);
#endif
