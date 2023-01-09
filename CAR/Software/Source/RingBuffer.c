#include "RingBuffer.h"

/*************************/

void RingBuffer_Init(ringBuffer_t *data)
{
	data->head=0;
	data->tail=0;
}

void RingBuffer_Write(ringBuffer_t *data,uint8_t *Temp)
{
	uint8_t i;
	data->ringBuf[data->tail]=*Temp;
	if(++data->tail>=MAX_SIZE)
		data->tail=0;
	if(data->tail==data->head)
		if(++data->head>=MAX_SIZE)
			data->head=0;
}

uint8_t RingBuffer_Read(ringBuffer_t *data,uint8_t *Temp)
{
	uint8_t i;
	taskENTER_CRITICAL();

	if(data->head==data->tail)//�����
	{
		taskEXIT_CRITICAL();	
		return 0;//�����
	}else 
	{
		*Temp=data->ringBuf[data->head];
		
		if(++data->head>=MAX_SIZE)  
			data->head=0;
	}

	taskEXIT_CRITICAL();	
	return 1;
}
 












