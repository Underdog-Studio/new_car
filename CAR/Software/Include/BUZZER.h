#ifndef __BUZZER_H
#define __BUZZER_H


#include "gpio_drv.h"
#include "timer_drv.h"

//������ʼ�
void BUZZER_Init(void);

void Buzzer_Disable(void);
void Set_Buzzer(uint16_t Freq,float Volume);


#endif

