#include "EXTI_drv.h"



static void (*EXTI5_Callback)(void);
static void (*EXTI11_Callback)(void);

void EXTI_Init()
{

	
	gpio_init(GPIOC,GPIO_MODE_IN_FLOATING,GPIO_OSPEED_50MHZ,GPIO_PIN_5|GPIO_PIN_11);
	
	nvic_irq_enable(EXTI10_15_IRQn,14,0);
	nvic_irq_enable(EXTI5_9_IRQn  ,13,0);
	
	
	gpio_exti_source_select(GPIO_PORT_SOURCE_GPIOC,GPIO_PIN_SOURCE_11);
	gpio_exti_source_select(GPIO_PORT_SOURCE_GPIOC,GPIO_PIN_SOURCE_5);
	
	exti_init(EXTI_11,EXTI_INTERRUPT,EXTI_TRIG_RISING);
	EXTI11_Callback = 0;
	exti_interrupt_flag_clear(EXTI_11);
	
	exti_init(EXTI_5,EXTI_INTERRUPT,EXTI_TRIG_RISING);
	EXTI5_Callback = 0;
	exti_interrupt_flag_clear(EXTI_5);
}

void EXTI5_Callback_Register(void(*app)(void))
{
	EXTI5_Callback=app;
}
void EXTI11_Callback_Register(void(*app)(void))
{
	EXTI11_Callback=app;
}


void EXTI10_15_IRQHandler(void)
{
	if((RESET != exti_interrupt_flag_get(EXTI_11))&&EXTI11_Callback!=0)
	{
		EXTI11_Callback();
	}
	exti_init(EXTI_11,EXTI_INTERRUPT,EXTI_TRIG_RISING);
}

void EXTI5_9_IRQHandler(void)
{
	if((RESET != exti_interrupt_flag_get(EXTI_5))&&EXTI5_Callback!=0)
	{
		EXTI5_Callback();
	}
	exti_init(EXTI_5,EXTI_INTERRUPT,EXTI_TRIG_RISING);
}

