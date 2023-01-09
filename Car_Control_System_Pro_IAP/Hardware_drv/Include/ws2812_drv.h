/**************************
*Description :ws2812驱动
*Author      :18电信赵华磊
*Date        :2022/04/07
*Function    :驱动ws2812 LED
						 
**************************/
#ifndef __ws2812_drv_H
#define __ws2812_drv_H

#include "gd32f30x_spi.h"
typedef struct
{
		void(*Init)(void);
}ws2812_byte;

#define Code0 0x07FF
#define Code1 0X001F
#define CodeR 100
void ws2812_Init(void);
void ws2812_Control(uint8_t R,uint8_t G,uint8_t B);

#define ws28121 ws2812

#endif




