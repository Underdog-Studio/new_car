#include "Encoder_drv.h"

static void Encoder_Gpio_Init(void);
static void Encoder_Timer_Init(void);
static Encoder_Type Time1,Time2,Time3,Time4;

void Encoder_Init(void)
{
	Encoder_Gpio_Init();
	Encoder_Timer_Init();
}

static void Encoder_Gpio_Init(void)
{
//	 rcu_periph_clock_enable(RCU_AF);				
	 rcu_periph_clock_enable(RCU_GPIOB);
	
	 gpio_pin_remap_config(GPIO_SWJ_SWDPENABLE_REMAP,ENABLE);
	 gpio_pin_remap_config(GPIO_TIMER1_PARTIAL_REMAP0,ENABLE);
	 //T1
	 gpio_init(GPIOA, GPIO_MODE_IN_FLOATING, GPIO_OSPEED_50MHZ, GPIO_PIN_15);
	 gpio_init(GPIOB, GPIO_MODE_IN_FLOATING, GPIO_OSPEED_50MHZ, GPIO_PIN_3);

	 //T2
	 gpio_init(GPIOA, GPIO_MODE_IN_FLOATING, GPIO_OSPEED_50MHZ, GPIO_PIN_6|GPIO_PIN_7);
	 //T3
	 gpio_init(GPIOB, GPIO_MODE_IN_FLOATING, GPIO_OSPEED_50MHZ, GPIO_PIN_6|GPIO_PIN_7);
	 //T4
	 gpio_init(GPIOA, GPIO_MODE_IN_FLOATING, GPIO_OSPEED_50MHZ, GPIO_PIN_0|GPIO_PIN_1);
}



static void Encoder_Timer_Init(void)
{
	  timer_ic_parameter_struct timer_icinitpara;
    timer_parameter_struct timer_initpara;

	  rcu_periph_clock_enable(RCU_TIMER1);
	
	  timer_deinit(TIMER1);
    timer_struct_para_init(&timer_initpara);
    timer_initpara.prescaler         = 0;
    timer_initpara.alignedmode       = TIMER_COUNTER_EDGE;
    timer_initpara.counterdirection  = TIMER_COUNTER_UP;
    timer_initpara.period            = 0xffff;   
    timer_initpara.clockdivision     = TIMER_CKDIV_DIV1;
    timer_initpara.repetitioncounter = 0;
    timer_init(TIMER1, &timer_initpara);    

    timer_channel_input_struct_para_init(&timer_icinitpara);
    timer_icinitpara.icpolarity  =  TIMER_IC_POLARITY_RISING;
    timer_icinitpara.icselection = TIMER_IC_SELECTION_DIRECTTI;
    timer_icinitpara.icprescaler = TIMER_IC_PSC_DIV1;
    timer_icinitpara.icfilter    = 0x0;
    timer_input_capture_config(TIMER1,TIMER_CH_0,&timer_icinitpara);
    timer_input_capture_config(TIMER1,TIMER_CH_1,&timer_icinitpara);

    timer_quadrature_decoder_mode_config( TIMER1 ,TIMER_ENCODER_MODE2,TIMER_IC_POLARITY_FALLING, TIMER_IC_POLARITY_FALLING);
	timer_auto_reload_shadow_enable(TIMER1);

    timer_enable(TIMER1);
		
	  rcu_periph_clock_enable(RCU_TIMER2);
	
	  timer_deinit(TIMER2);
    timer_struct_para_init(&timer_initpara);
    timer_initpara.prescaler         = 0;
    timer_initpara.alignedmode       = TIMER_COUNTER_EDGE;
    timer_initpara.counterdirection  = TIMER_COUNTER_UP;
    timer_initpara.period            = 0xffff;   
    timer_initpara.clockdivision     = TIMER_CKDIV_DIV1;
    timer_initpara.repetitioncounter = 0;
    timer_init(TIMER2, &timer_initpara);    

    timer_channel_input_struct_para_init(&timer_icinitpara);
    timer_icinitpara.icpolarity  =  TIMER_IC_POLARITY_RISING;
    timer_icinitpara.icselection = TIMER_IC_SELECTION_DIRECTTI;
    timer_icinitpara.icprescaler = TIMER_IC_PSC_DIV1;
    timer_icinitpara.icfilter    = 0x0;
    timer_input_capture_config(TIMER2,TIMER_CH_0,&timer_icinitpara);
    timer_input_capture_config(TIMER2,TIMER_CH_1,&timer_icinitpara);

    timer_quadrature_decoder_mode_config( TIMER2 ,TIMER_ENCODER_MODE2,TIMER_IC_POLARITY_FALLING, TIMER_IC_POLARITY_FALLING);
		timer_auto_reload_shadow_enable(TIMER2);
		
		
    timer_enable(TIMER2);
	  rcu_periph_clock_enable(RCU_TIMER3);
	
	  timer_deinit(TIMER3);
    timer_struct_para_init(&timer_initpara);
    timer_initpara.prescaler         = 0;
    timer_initpara.alignedmode       = TIMER_COUNTER_EDGE;
    timer_initpara.counterdirection  = TIMER_COUNTER_UP;
    timer_initpara.period            = 0xffff;   
    timer_initpara.clockdivision     = TIMER_CKDIV_DIV1;
    timer_initpara.repetitioncounter = 0;
    timer_init(TIMER3, &timer_initpara);    

    timer_channel_input_struct_para_init(&timer_icinitpara);
    timer_icinitpara.icpolarity  =  TIMER_IC_POLARITY_RISING;
    timer_icinitpara.icselection = TIMER_IC_SELECTION_DIRECTTI;
    timer_icinitpara.icprescaler = TIMER_IC_PSC_DIV1;
    timer_icinitpara.icfilter    = 0x0;
    timer_input_capture_config(TIMER3,TIMER_CH_0,&timer_icinitpara);
    timer_input_capture_config(TIMER3,TIMER_CH_1,&timer_icinitpara);

    timer_quadrature_decoder_mode_config( TIMER3 ,TIMER_ENCODER_MODE2,TIMER_IC_POLARITY_FALLING, TIMER_IC_POLARITY_FALLING);
		timer_auto_reload_shadow_enable(TIMER3);
		
		
    timer_enable(TIMER3);
		
	  rcu_periph_clock_enable(RCU_TIMER4);
	
	  timer_deinit(TIMER4);
    timer_struct_para_init(&timer_initpara);
    timer_initpara.prescaler         = 0;
    timer_initpara.alignedmode       = TIMER_COUNTER_EDGE;
    timer_initpara.counterdirection  = TIMER_COUNTER_UP;
    timer_initpara.period            = 0xffff;   
    timer_initpara.clockdivision     = TIMER_CKDIV_DIV1;
    timer_initpara.repetitioncounter = 0;
    timer_init(TIMER4, &timer_initpara);    

    timer_channel_input_struct_para_init(&timer_icinitpara);
    timer_icinitpara.icpolarity  =  TIMER_IC_POLARITY_RISING;
    timer_icinitpara.icselection = TIMER_IC_SELECTION_DIRECTTI;
    timer_icinitpara.icprescaler = TIMER_IC_PSC_DIV1;
    timer_icinitpara.icfilter    = 0x0;
    timer_input_capture_config(TIMER4,TIMER_CH_0,&timer_icinitpara);
    timer_input_capture_config(TIMER4,TIMER_CH_1,&timer_icinitpara);

    timer_quadrature_decoder_mode_config( TIMER4 ,TIMER_ENCODER_MODE2,TIMER_IC_POLARITY_FALLING, TIMER_IC_POLARITY_FALLING);
		timer_auto_reload_shadow_enable(TIMER4);
		
		
    timer_enable(TIMER4);
}
		
void TIMER1_IRQHandler(void)
{
	if(timer_interrupt_flag_get(TIMER1,TIMER_INT_FLAG_UP)==SET)
	{
		if((TIMER_CTL0(TIMER1)&TIMER_CTL0_DIR)==TIMER_CTL0_DIR)
			Time1.Overflow_Make--;
		else
			Time1.Overflow_Make++;
		timer_interrupt_flag_clear(TIMER1,TIMER_INT_FLAG_UP);
	}
}
void TIMER2_IRQHandler(void)
{
	if(timer_interrupt_flag_get(TIMER2,TIMER_INT_FLAG_UP)==SET)
	{
		if((TIMER_CTL0(TIMER2)&TIMER_CTL0_DIR)==TIMER_CTL0_DIR)
			Time2.Overflow_Make--;
		else
			Time2.Overflow_Make++;
		timer_interrupt_flag_clear(TIMER2,TIMER_INT_FLAG_UP);
	}
}
void TIMER3_IRQHandler(void)
{
	if(timer_interrupt_flag_get(TIMER3,TIMER_INT_FLAG_UP)==SET)
	{
		if((TIMER_CTL0(TIMER3)&TIMER_CTL0_DIR)==TIMER_CTL0_DIR)
			Time3.Overflow_Make--;
		else
			Time3.Overflow_Make++;
		timer_interrupt_flag_clear(TIMER3,TIMER_INT_FLAG_UP);
	}
}
void TIMER4_IRQHandler(void)
{
	if(timer_interrupt_flag_get(TIMER4,TIMER_INT_FLAG_UP)==SET)
	{
		if((TIMER_CTL0(TIMER4)&TIMER_CTL0_DIR)==TIMER_CTL0_DIR)
			Time4.Overflow_Make--;
		else
			Time4.Overflow_Make++;
		timer_interrupt_flag_clear(TIMER4,TIMER_INT_FLAG_UP);
	}
}





Encoder_Type Get_Timer_Pulse(uint8_t Tnum)
{
	switch(Tnum)
	{
		case T1:
		{
			Time1.Pluse = (int16_t)timer_counter_read(TIMER1);
			if(Time1.Pluse > -10)
				Time1.Overflow_Make = 0;
			timer_counter_value_config(TIMER1,0);
			Time1.T = Get_deta_T(Time1.Last_T);
			Time1.Last_T = Get_System_T();
			return Time1;	
		}
		case T2:
		{
			Time2.Pluse = (int16_t)timer_counter_read(TIMER2);
			if(Time2.Pluse > -10)
				Time2.Overflow_Make = 0;
			timer_counter_value_config(TIMER2,0);
			Time2.T = Get_deta_T(Time2.Last_T);
			Time2.Last_T = Get_System_T();
			return Time2;		
		}
		case T3:
		{
			Time3.Pluse = (int16_t)timer_counter_read(TIMER3);
			if(Time3.Pluse > -10)
				Time3.Overflow_Make = 0;
			timer_counter_value_config(TIMER3,0);
			Time3.T = Get_deta_T(Time3.Last_T);
			Time3.Last_T = Get_System_T();
			return Time3;	
		}
		case T4:
		{
			Time4.Pluse = (int16_t)timer_counter_read(TIMER4);
			if(Time4.Pluse > -10)
				Time4.Overflow_Make = 0;
			timer_counter_value_config(TIMER4,0);
			Time4.T = Get_deta_T(Time4.Last_T);
			Time4.Last_T = Get_System_T();
			return Time4;	
		}
	}
	return Time4;
}



