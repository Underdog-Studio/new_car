/**************************
*Description:        /环形数据缓冲区
*Author:             /18电信赵华磊
*Date:               /2019/12/22
*Program Assignment: /缓冲数据

**************************/
/*******头文件引用********/
#include "gd32f30x.h"

/*************************/

#ifndef __RingBuffer_H
#define __RingBuffer_H




#define MAX_SIZE  2048//缓冲区大小



typedef struct

{
uint16_t head;//缓冲区头部位置

uint16_t tail;//缓冲区尾部位置

uint8_t ringBuf[MAX_SIZE];//缓冲区数组

} ringBuffer_t;


void RingBuffer_Init(ringBuffer_t *data);
void RingBuffer_Write(ringBuffer_t *data,uint8_t *Temp,uint8_t num);
uint8_t RingBuffer_Read(ringBuffer_t *data,uint8_t *Temp,uint8_t num);




#endif
