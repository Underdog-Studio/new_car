#include "gd32f30x.h"

#include "FreeRTOS.h"
#include "task.h"

/*************************/

#ifndef __RingBuffer_H
#define __RingBuffer_H




#define MAX_SIZE  512//���������������С



typedef struct

{
    uint16_t head;//�����������ͷ���λ���

    uint16_t tail;//�����������β���λ���

    uint8_t ringBuf[MAX_SIZE];//�������������������

} ringBuffer_t;


void RingBuffer_Init(ringBuffer_t *data);
void RingBuffer_Write(ringBuffer_t *data,uint8_t *Temp);
uint8_t RingBuffer_Read(ringBuffer_t *data,uint8_t *Temp);




#endif
