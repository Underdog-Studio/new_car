
#include "timer_drv.h"


static void (*TIMER5_Callback)(void);
void timer5_init(void)
{
	rcu_periph_clock_enable(RCU_TIMER5);
	
	timer_parameter_struct timer_initparam;
	
	timer_initparam.prescaler=10-1;           
	timer_initparam.alignedmode=TIMER_COUNTER_EDGE;               
	timer_initparam.counterdirection=TIMER_COUNTER_DOWN;            
	timer_initparam.period=1000-1;                                
	timer_initparam.clockdivision=TIMER_CKDIV_DIV1;             
	timer_initparam.repetitioncounter=0;                      
	timer_init(TIMER5,&timer_initparam);
	
	timer_interrupt_flag_clear(TIMER5,TIMER_INT_FLAG_UP);
	nvic_irq_enable(TIMER5_IRQn,5,0);
	timer_interrupt_enable(TIMER5,TIMER_INT_UP);
	TIMER5_Callback = 0x0000;
	timer_disable(TIMER5);
}
void TIMER5_IRQHandler(void)
{
	if((timer_interrupt_flag_get(TIMER5,TIMER_INT_FLAG_UP)==SET)&&TIMER5_Callback!=0x0000)
	{		
		TIMER5_Callback();
		timer_interrupt_flag_clear(TIMER5,TIMER_INT_FLAG_UP);
	}
}
void TIMER5_Callback_Register(void(*app)(void))
{
	TIMER5_Callback=app;
}
static void (*TIMER6_Callback)(void);
void timer6_init(void)
{
	rcu_periph_clock_enable(RCU_TIMER6);
	
	timer_parameter_struct timer_initparam;
	
	timer_initparam.prescaler=10-1;           
	timer_initparam.alignedmode=TIMER_COUNTER_EDGE;               
	timer_initparam.counterdirection=TIMER_COUNTER_DOWN;            
	timer_initparam.period=20000-1;                                  
	timer_initparam.clockdivision=TIMER_CKDIV_DIV1;              
	timer_initparam.repetitioncounter=0;                         
	timer_init(TIMER6,&timer_initparam);
	
	timer_interrupt_flag_clear(TIMER6,TIMER_INT_FLAG_UP);
	nvic_irq_enable(TIMER6_IRQn,6,0);
	timer_interrupt_enable(TIMER6,TIMER_INT_UP);
	TIMER6_Callback = 0x0000;
	timer_disable(TIMER6);
}


void TIMER6_IRQHandler(void)
{
	if((timer_interrupt_flag_get(TIMER6,TIMER_INT_FLAG_UP)==SET)&&TIMER6_Callback!=0x0000)
	{		
		TIMER6_Callback();
		timer_interrupt_flag_clear(TIMER6,TIMER_INT_FLAG_UP);
	}
}

void TIMER6_Callback_Register(void(*app)(void))
{
	TIMER6_Callback=app;
}




