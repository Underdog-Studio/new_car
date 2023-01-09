#ifndef __timer_drv_H
#define __timer_drv_H

#include "gd32f30x_rcu.h"
#include "gd32f30x_timer.h"


void timer5_init(void);
void TIMER5_Callback_Register(void(*app)(void));

void timer6_init(void);
void TIMER6_Callback_Register(void(*app)(void));

#endif
