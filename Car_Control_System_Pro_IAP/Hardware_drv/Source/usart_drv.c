
#include "usart_drv.h"



static void (*USART0_Callback)(uint8_t data);

void usart0_init(uint32_t baudrate)
{

	rcu_periph_clock_enable(RCU_GPIOA);

	rcu_periph_clock_enable(RCU_USART0);
	gpio_init(GPIOA,GPIO_MODE_AF_PP,GPIO_OSPEED_50MHZ,GPIO_PIN_9);
	gpio_init(GPIOA,GPIO_MODE_IN_FLOATING,GPIO_OSPEED_50MHZ,GPIO_PIN_10);


	rcu_periph_clock_enable(RCU_USART0);
	
	
	nvic_irq_enable(USART0_IRQn,2,0);
	
	usart_deinit(USART0);
	usart_baudrate_set(USART0,baudrate);
	usart_parity_config(USART0,USART_PM_NONE);
	usart_word_length_set(USART0,USART_WL_8BIT);
	usart_stop_bit_set(USART0,USART_STB_1BIT);
	usart_hardware_flow_rts_config(USART0,USART_RTS_DISABLE);
	usart_hardware_flow_cts_config(USART0,USART_CTS_DISABLE);
	usart_receive_config(USART0,USART_RECEIVE_ENABLE);
	usart_transmit_config(USART0,USART_TRANSMIT_ENABLE);
	
	usart_interrupt_enable(USART0, USART_INT_RBNE);
	usart_enable(USART0);
	USART0_Callback=0x0000;

}

void usart0_send_byte(uint8_t c)
{
	while(usart_flag_get(USART0, USART_FLAG_TBE) == RESET){}
  usart_data_transmit(USART0, c);
}

void USART0_IRQHandler(void)
{
	if(usart_interrupt_flag_get(USART0,USART_INT_FLAG_RBNE)!=RESET && USART0_Callback!=0)
	{
		USART0_Callback((uint8_t)usart_data_receive(USART0));
	}
  usart_interrupt_flag_clear(USART0,USART_INT_FLAG_RBNE);
}
void USART0_IRQ_Callback_Register(void(*app)(uint8_t))
{
	USART0_Callback=app;
}




static void (*USART1_Callback)(uint8_t data);

void usart1_init(uint32_t baudrate)
{

	rcu_periph_clock_enable(RCU_GPIOA);

	rcu_periph_clock_enable(RCU_USART1);
	gpio_init(GPIOA,GPIO_MODE_AF_PP,GPIO_OSPEED_50MHZ,GPIO_PIN_2);
	gpio_init(GPIOA,GPIO_MODE_IN_FLOATING,GPIO_OSPEED_50MHZ,GPIO_PIN_3);


	rcu_periph_clock_enable(RCU_USART1);
	
	
	nvic_irq_enable(USART1_IRQn,3,0);
	
	usart_deinit(USART1);
	usart_baudrate_set(USART1,baudrate);
	usart_parity_config(USART1,USART_PM_NONE);
	usart_word_length_set(USART1,USART_WL_8BIT);
	usart_stop_bit_set(USART1,USART_STB_1BIT);
	usart_hardware_flow_rts_config(USART1,USART_RTS_DISABLE);
	usart_hardware_flow_cts_config(USART1,USART_CTS_DISABLE);
	usart_receive_config(USART1,USART_RECEIVE_ENABLE);
	usart_transmit_config(USART1,USART_TRANSMIT_ENABLE);
	
	usart_interrupt_enable(USART1, USART_INT_RBNE);
	usart_enable(USART1);
	USART1_Callback=0x0000;

}

void usart1_send_byte(uint8_t c)
{
	while(usart_flag_get(USART1, USART_FLAG_TBE) == RESET){}
  usart_data_transmit(USART1, c);
}

void USART1_IRQHandler(void)
{
	if(usart_interrupt_flag_get(USART1,USART_INT_FLAG_RBNE)!=RESET && USART1_Callback!=0)
	{
		USART1_Callback((uint8_t)usart_data_receive(USART1));
	}
  usart_interrupt_flag_clear(USART1,USART_INT_FLAG_RBNE);
}

void USART1_IRQ_Callback_Register(void(*app)(uint8_t))
{
	USART1_Callback=app;
}


static void (*USART2_Callback)(uint8_t data);

void usart2_init(uint32_t baudrate)
{

	rcu_periph_clock_enable(RCU_GPIOB);

	rcu_periph_clock_enable(RCU_USART2);
	gpio_init(GPIOB,GPIO_MODE_AF_PP,GPIO_OSPEED_50MHZ,GPIO_PIN_10);
	gpio_init(GPIOB,GPIO_MODE_IN_FLOATING,GPIO_OSPEED_50MHZ,GPIO_PIN_11);

	rcu_periph_clock_enable(RCU_USART2);
	
	
	nvic_irq_enable(USART2_IRQn,1,0);
	
	usart_deinit(USART2);
	usart_baudrate_set(USART2,baudrate);
	usart_parity_config(USART2,USART_PM_NONE);
	usart_word_length_set(USART2,USART_WL_8BIT);
	usart_stop_bit_set(USART2,USART_STB_1BIT);
	usart_hardware_flow_rts_config(USART2,USART_RTS_DISABLE);
	usart_hardware_flow_cts_config(USART2,USART_CTS_DISABLE);
	usart_receive_config(USART2,USART_RECEIVE_ENABLE);
	usart_transmit_config(USART2,USART_TRANSMIT_ENABLE);
	
	usart_interrupt_enable(USART2, USART_INT_RBNE);
	usart_enable(USART2);
	USART2_Callback=0x0000;

}


void usart2_send_byte(uint8_t c)
{
	while(usart_flag_get(USART2, USART_FLAG_TBE) == RESET){}
  usart_data_transmit(USART2, c);
}

void USART2_IRQHandler(void)
{
	if(usart_interrupt_flag_get(USART2,USART_INT_FLAG_RBNE)!=RESET && USART2_Callback!=0)
	{
		USART2_Callback((uint8_t)usart_data_receive(USART2));
	}
  usart_interrupt_flag_clear(USART2,USART_INT_FLAG_RBNE);
}

void USART2_IRQ_Callback_Register(void(*app)(uint8_t))
{
	USART2_Callback=app;
}




