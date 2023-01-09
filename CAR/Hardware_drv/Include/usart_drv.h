#ifndef __usart_drv_H
#define __usart_drv_H


#include "gd32f30x_usart.h"
#include "RingBuffer.h"

typedef struct 
{
    uint32_t UsartPort;
    uint32_t Baudval;
    uint32_t RxConfig;
    uint32_t TxConfig;
    uint32_t Paritycfg;
    uint32_t Wlen;
    uint32_t Stblen;
    uint32_t RTSConfig;
    uint32_t CTSConfig;

    int8_t RxIntPriority;
    void (*RxCallback)(uint8_t data);
    int8_t TxIntPriority;
    void (*TxCallback)(uint8_t data);
    
    uint8_t RxBufferConfig;
    uint8_t RxBufferData[512];
    ringBuffer_t RxBuffer;
}USART_Class_t;




void usart0_init(uint32_t baudrate);
void usart0_send_byte(uint8_t c);
void USART0_IRQ_Callback_Register(void(*app)(uint8_t));

void usart1_init(uint32_t baudrate);
void usart1_send_byte(uint8_t c);
void USART1_IRQ_Callback_Register(void(*app)(uint8_t));

void usart2_init(uint32_t baudrate);
void usart2_send_byte(uint8_t c);
void USART2_IRQ_Callback_Register(void(*app)(uint8_t));
 
void usart3_init(uint32_t baudrate);
void usart3_send_byte(uint8_t c);
void USART3_IRQ_Callback_Register(void(*app)(uint8_t));

void usart4_init(uint32_t baudrate);
void usart4_send_byte(uint8_t c);
void USART4_IRQ_Callback_Register(void(*app)(uint8_t));
#endif

