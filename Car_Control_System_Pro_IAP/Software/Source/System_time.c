
#include "System_time.h"

/*************************/



//初始化滴答定时器  1ms中断
Time System_T;
uint16_t us_Count;

/*
*@ Description :系统时钟初始化
*/
void System_time_init(void)
{
	SysTick_Config(SystemCoreClock/1000);	
	System_T.s=0;
	System_T.ms=0;
	System_T.us=0;
	us_Count = SystemCoreClock/1000000;
}


/*
*@ Description :滴答定时器中断处理函数
*/
void SysTick_Handler(void)
{
		System_T.ms++;
		if(System_T.ms>=1000)
		{
			System_T.ms=0;
			System_T.s++;
		}
}

/*
*@ Description :获取系统时钟
*@ return      :系统时钟
*/
Time Get_System_T(void)
{
	System_T.us=1000-((SysTick->VAL)/us_Count);
	return System_T;
}

/*
*@ Description :获取时间间隔
*@ return      :时间间隔(单位 秒)
*/
float Get_deta_T(Time T)
{
	return (System_T.s-T.s)
					+(System_T.ms-T.ms)/1000.0f
					+(Get_System_T().us-T.us)/1000000.0f;
}

/*
*@ Description :微秒延时
*@ param 1     :延时时间
*/
void delay_us(uint32_t nus)
{
	Time Last_T=Get_System_T();
	while((Get_deta_T(Last_T))<=nus/1000000.0f);
}
	
/*
*@ Description :毫秒延时
*@ param 1     :延时时间
*/
void delay_ms(uint16_t nms)
{
 	Time Last_T=Get_System_T();
	while((Get_deta_T(Last_T))<=nms/1000.0f);
}


