#include "pwm_drv.h"

static void RCU_TIME_ENABLE(uint32_t TIME);

static void pwm_gpio_init(void)
{
	#ifdef PWMTIME_A
		//CH0--A
		gpio_init(GPIOA, GPIO_MODE_AF_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_8);
		//CH1--B
		gpio_init(GPIOA, GPIO_MODE_AF_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_9);
		//CH2--C
		gpio_init(GPIOA, GPIO_MODE_AF_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_10);
		//CH3--D
		gpio_init(GPIOA, GPIO_MODE_AF_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_11);
	#endif
	#ifdef PWMTIME_B
		//CH0--E
		gpio_init(GPIOC, GPIO_MODE_AF_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_6);
	  //CH1--F
		gpio_init(GPIOC, GPIO_MODE_AF_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_7);
	  //CH2--G
		gpio_init(GPIOC, GPIO_MODE_AF_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_8);
	  //CH3--H
		gpio_init(GPIOC, GPIO_MODE_AF_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_9);
	#endif
}


static void pwm_time_init(void)
{
	timer_parameter_struct timer_initparam;
	timer_oc_parameter_struct timer_ocinitparam;
	#ifdef PWMTIME_A
		RCU_TIME_ENABLE(PWMTIME_A);
		timer_deinit(PWMTIME_A);
		
		timer_initparam.prescaler=0;                                  
		timer_initparam.alignedmode=TIMER_COUNTER_EDGE;               
		timer_initparam.counterdirection=TIMER_COUNTER_UP;            
		timer_initparam.period=PERIOD_A;                               
		timer_initparam.clockdivision=TIMER_CKDIV_DIV1;               
		timer_initparam.repetitioncounter=0;                         
		timer_init(PWMTIME_A,&timer_initparam);
		
		timer_ocinitparam.outputstate = TIMER_CCX_ENABLE;          
		timer_ocinitparam.ocpolarity = TIMER_OC_POLARITY_HIGH;     
		timer_ocinitparam.ocnidlestate = TIMER_OC_IDLE_STATE_LOW;   
		
		timer_channel_output_config(PWMTIME_A,PWMA_H_CH,&timer_ocinitparam);
		timer_channel_output_config(PWMTIME_A,PWMB_H_CH,&timer_ocinitparam);
		timer_channel_output_config(PWMTIME_A,PWMC_H_CH,&timer_ocinitparam);
		timer_channel_output_config(PWMTIME_A,PWMD_H_CH,&timer_ocinitparam);

		timer_channel_output_pulse_value_config(PWMTIME_A,PWMA_H_CH,0);
		timer_channel_output_pulse_value_config(PWMTIME_A,PWMB_H_CH,0);
		timer_channel_output_pulse_value_config(PWMTIME_A,PWMC_H_CH,0);
		timer_channel_output_pulse_value_config(PWMTIME_A,PWMD_H_CH,0);

		timer_channel_output_mode_config(PWMTIME_A,PWMA_H_CH,TIMER_OC_MODE_PWM0);
		timer_channel_output_mode_config(PWMTIME_A,PWMB_H_CH,TIMER_OC_MODE_PWM0);
		timer_channel_output_mode_config(PWMTIME_A,PWMC_H_CH,TIMER_OC_MODE_PWM0);
		timer_channel_output_mode_config(PWMTIME_A,PWMD_H_CH,TIMER_OC_MODE_PWM0);

		timer_channel_output_shadow_config(PWMTIME_A,PWMA_H_CH,TIMER_OC_SHADOW_ENABLE);
		timer_channel_output_shadow_config(PWMTIME_A,PWMB_H_CH,TIMER_OC_SHADOW_ENABLE);
		timer_channel_output_shadow_config(PWMTIME_A,PWMC_H_CH,TIMER_OC_SHADOW_ENABLE);
		timer_channel_output_shadow_config(PWMTIME_A,PWMD_H_CH,TIMER_OC_SHADOW_ENABLE);

		timer_primary_output_config(PWMTIME_A,ENABLE);
		timer_enable(PWMTIME_A);
	#endif
	#ifdef PWMTIME_B
		RCU_TIME_ENABLE(PWMTIME_B);
		timer_deinit(PWMTIME_B);
		
		timer_initparam.prescaler=100-1;                                  
		timer_initparam.alignedmode=TIMER_COUNTER_EDGE;              
		timer_initparam.counterdirection=TIMER_COUNTER_UP;            
		timer_initparam.period=PERIOD_B;                                
		timer_initparam.clockdivision=TIMER_CKDIV_DIV1;               
		timer_initparam.repetitioncounter=0;                         
		timer_init(PWMTIME_B,&timer_initparam);
		
		timer_ocinitparam.outputstate = TIMER_CCX_ENABLE;          
		timer_ocinitparam.ocpolarity = TIMER_OC_POLARITY_HIGH;      
		timer_ocinitparam.ocnidlestate = TIMER_OC_IDLE_STATE_LOW;   
		
		timer_channel_output_config(PWMTIME_B,PWME_H_CH,&timer_ocinitparam);
		timer_channel_output_config(PWMTIME_B,PWMF_H_CH,&timer_ocinitparam);
		timer_channel_output_config(PWMTIME_B,PWMG_H_CH,&timer_ocinitparam);
		timer_channel_output_config(PWMTIME_B,PWMH_H_CH,&timer_ocinitparam);

		timer_channel_output_pulse_value_config(PWMTIME_B,PWME_H_CH,0);
		timer_channel_output_pulse_value_config(PWMTIME_B,PWMF_H_CH,0);
		timer_channel_output_pulse_value_config(PWMTIME_B,PWMG_H_CH,0);
		timer_channel_output_pulse_value_config(PWMTIME_B,PWMH_H_CH,0);

		timer_channel_output_mode_config(PWMTIME_B,PWME_H_CH,TIMER_OC_MODE_PWM0);
		timer_channel_output_mode_config(PWMTIME_B,PWMF_H_CH,TIMER_OC_MODE_PWM0);
		timer_channel_output_mode_config(PWMTIME_B,PWMG_H_CH,TIMER_OC_MODE_PWM0);
		timer_channel_output_mode_config(PWMTIME_B,PWMH_H_CH,TIMER_OC_MODE_PWM0);

		timer_channel_output_shadow_config(PWMTIME_B,PWME_H_CH,TIMER_OC_SHADOW_ENABLE);
		timer_channel_output_shadow_config(PWMTIME_B,PWMF_H_CH,TIMER_OC_SHADOW_ENABLE);
		timer_channel_output_shadow_config(PWMTIME_B,PWMG_H_CH,TIMER_OC_SHADOW_ENABLE);
		timer_channel_output_shadow_config(PWMTIME_B,PWMH_H_CH,TIMER_OC_SHADOW_ENABLE);

		timer_primary_output_config(PWMTIME_B,ENABLE);
		timer_enable(PWMTIME_B);
	#endif
}


void pwm_init(void)
{
	pwm_gpio_init();
	pwm_time_init();
}


static void RCU_TIME_ENABLE(uint32_t TIME)
{
	switch(TIME)
	{
		case TIMER0:
			rcu_periph_clock_enable(RCU_TIMER0);
		break;
		case TIMER2:
			rcu_periph_clock_enable(RCU_TIMER2);
		break;	
		case TIMER7:
			rcu_periph_clock_enable(RCU_TIMER7);
		break;
	}
}


uint8_t Set_PWM_Duty(uint16_t PWMn,float Duty)
{
	uint16_t Pulse;
	if(PWMn<5)
	{
		Pulse=(uint16_t)(Duty/100*PERIOD_A);
		if(Duty>100||Duty<0)
			return 0;
	}else
	{
		Pulse=(uint16_t)(Duty/100*PERIOD_B);
		if(Duty>100||Duty<0)
			return 0;
	}
	switch(PWMn)
	{
		case PWMA:
			timer_channel_output_pulse_value_config(PWMTIME_A,PWMA_H_CH,Pulse);
		break;
		case PWMB:
			timer_channel_output_pulse_value_config(PWMTIME_A,PWMB_H_CH,Pulse);
		break;
		case PWMC:
			timer_channel_output_pulse_value_config(PWMTIME_A,PWMC_H_CH,Pulse);
		break;
		case PWMD:
			timer_channel_output_pulse_value_config(PWMTIME_A,PWMD_H_CH,Pulse);
		break;
		case PWME:
			timer_channel_output_pulse_value_config(PWMTIME_B,PWME_H_CH,Pulse);
		break;
		case PWMF:
			timer_channel_output_pulse_value_config(PWMTIME_B,PWMF_H_CH,Pulse);
		break;
		case PWMG:
			timer_channel_output_pulse_value_config(PWMTIME_B,PWMG_H_CH,Pulse);
		break;
		case PWMH:
			timer_channel_output_pulse_value_config(PWMTIME_B,PWMH_H_CH,Pulse);
		break;
	}
	return 1;
}


void Set_PWM_Freq(uint32_t TIME,uint16_t Freq)
{
	switch(TIME)
	{
		case TIMER0:
			Freq = SystemCoreClock/Freq;
			timer_prescaler_config(TIMER0,Freq,TIMER_PSC_RELOAD_UPDATE);
		break;
		case TIMER7:
			Freq = SystemCoreClock/Freq;
		  timer_prescaler_config(TIMER7,Freq,TIMER_PSC_RELOAD_UPDATE);
		break;
	}
}

