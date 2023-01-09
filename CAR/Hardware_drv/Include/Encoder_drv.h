#ifndef __Encoder_drv_H
#define __Encoder_drv_H

#include "gd32f30x_timer.h"
#include "gd32f30x_rcu.h"
#include "System_time.h"


#define T1 1
#define T2 2
#define T3 3
#define T4 4


typedef struct
{
	int8_t Overflow_Make;
	int16_t Last_Pluse;
	Time Last_T;
	int16_t Pluse;
	float T;
}Encoder_Type;

void Encoder_Init(void);
Encoder_Type Get_Timer_Pulse(uint8_t Tnum);
#endif

