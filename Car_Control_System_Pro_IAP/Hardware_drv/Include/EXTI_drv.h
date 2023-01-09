#ifndef __EXTI_drv_H
#define __EXTI_drv_H

#include "gd32f30x_exti.h"
#include "gd32f30x_gpio.h"

void EXTI_Init();
void EXTI5_Callback_Register(void(*app)(void));
void EXTI11_Callback_Register(void(*app)(void));
#endif
