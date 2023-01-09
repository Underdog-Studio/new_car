#ifndef __usart_drv_H
#define __usart_drv_H


#include "gd32f30x_usart.h"
#include "RingBuffer.h"




void usart0_init(uint32_t baudrate);
void usart0_send_byte(uint8_t c);
void USART0_IRQ_Callback_Register(void(*app)(uint8_t));

void usart1_init(uint32_t baudrate);
void usart1_send_byte(uint8_t c);
void USART1_IRQ_Callback_Register(void(*app)(uint8_t));

void usart2_init(uint32_t baudrate);
void usart2_send_byte(uint8_t c);
void USART2_IRQ_Callback_Register(void(*app)(uint8_t));

#endif

