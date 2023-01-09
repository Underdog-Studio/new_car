#include "BUZZER.h"
gpio_control BUZZER;
void Buzzer_High_Callback(void);
void Buzzer_Low_Callback(void);
/*
*@ Description ????? ?????
*@ param ?????
*@ return ?????
*/
void BUZZER_Init(void)
{
	BUZZER = get_gpio_struct(4);
	timer5_init();
	timer6_init();
	TIMER5_Callback_Register(Buzzer_High_Callback);
	TIMER6_Callback_Register(Buzzer_Low_Callback);
}
void Buzzer_High_Callback(void)
{
	timer_disable(TIMER5);
	BUZZER.GPIO_LOW();
	timer_interrupt_flag_clear(TIMER6,TIMER_INT_FLAG_UP);
	timer_enable(TIMER6);
}
void Buzzer_Low_Callback(void)
{
	timer_disable(TIMER6);
	BUZZER.GPIO_HIGH();
	timer_interrupt_flag_clear(TIMER5,TIMER_INT_FLAG_UP);
	timer_enable(TIMER5);
}


void Set_Buzzer(uint16_t Freq,float Volume)
{
	uint16_t Freq_H,Freq_L,Freq_qq;
	
	Freq_qq = SystemCoreClock/10/Freq;//??????????
	
	Freq_H = (uint16_t)(Freq_qq*(Volume/100.0f));
	Freq_L = Freq_qq-Freq_H;
	timer_autoreload_value_config(TIMER5,Freq_H);
	timer_autoreload_value_config(TIMER6,Freq_L);
	
	
	BUZZER.GPIO_HIGH();
	timer_enable(TIMER5);
}


void Buzzer_Disable(void)
{
	timer_disable(TIMER5);
	timer_disable(TIMER6);
	BUZZER.GPIO_LOW();
}
