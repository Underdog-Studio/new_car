/**************************
*Description:        /滴答定时器系统实时时钟和延迟
*Author:             /18电信赵华磊
*Date:               /2019/12/15
*Program Assignment: /查询法延时 和提供系统实时时钟

**************************/
#include "gd32f30x.h"
#include "core_cm4.h"
/*************************/



#ifndef _System_time_H
#define _System_time_H

typedef struct
{
	uint32_t s;
	uint16_t ms;
	uint16_t us;
}Time;//时间数据

void System_time_init(void);
Time Get_System_T(void);
float Get_deta_T(Time T);
void delay_ms(uint16_t nms);
void delay_us(uint32_t nus);













#endif



