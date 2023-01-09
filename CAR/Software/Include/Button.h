#ifndef __Button_H
#define __Button_H


#include "EXTI_drv.h"
#include "FreeRTOS.h"
#include "semphr.h"



#define A 1
#define B 2

void Button_Init(void);
uint8_t Get_Button(char KEY);
SemaphoreHandle_t Get_Button_SemapHore(uint8_t Button);
#endif

