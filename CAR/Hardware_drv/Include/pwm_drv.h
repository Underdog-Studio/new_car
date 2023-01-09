
#ifndef __pwm_drv_H
#define __pwm_drv_H

#include "gd32f30x_timer.h"



#define PERIOD_A 4000
#define PWMTIME_A TIMER0 
#define PERIOD_B 24000
#define PWMTIME_B TIMER7

#define PWMA 1
#define PWMB 2
#define PWMC 3
#define PWMD 4
#define PWME 5
#define PWMF 6
#define PWMG 7
#define PWMH 8

#define PWMA_H_CH TIMER_CH_0
#define PWMB_H_CH TIMER_CH_1
#define PWMC_H_CH TIMER_CH_2
#define PWMD_H_CH TIMER_CH_3
#define PWME_H_CH TIMER_CH_0
#define PWMF_H_CH TIMER_CH_1
#define PWMG_H_CH TIMER_CH_2
#define PWMH_H_CH TIMER_CH_3
void pwm_init(void);
uint8_t Set_PWM_Duty(uint16_t PWMn,float Duty);
void Set_PWM_Freq(uint32_t TIME,uint16_t Freq);
#endif

