#include "gd32f30x_it.h"

#include "ws2812_drv.h"
#include "System_time.h"

extern ws2812_byte ws2812;

int main(void)
{
	//ws2812_Init();
	System_time_init();
	while(1)
	{
		ws28121.Init();
		delay_ms(100);
		//ws2812_Control(255,0,0);
		delay_ms(100);
		//ws2812_Control(0,255,0);
		delay_ms(100);
		//ws2812_Control(0,0,255);
	}
}




