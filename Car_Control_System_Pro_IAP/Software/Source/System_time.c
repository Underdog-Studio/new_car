
#include "System_time.h"

/*************************/



//��ʼ���δ�ʱ��  1ms�ж�
Time System_T;
uint16_t us_Count;

/*
*@ Description :ϵͳʱ�ӳ�ʼ��
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
*@ Description :�δ�ʱ���жϴ�����
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
*@ Description :��ȡϵͳʱ��
*@ return      :ϵͳʱ��
*/
Time Get_System_T(void)
{
	System_T.us=1000-((SysTick->VAL)/us_Count);
	return System_T;
}

/*
*@ Description :��ȡʱ����
*@ return      :ʱ����(��λ ��)
*/
float Get_deta_T(Time T)
{
	return (System_T.s-T.s)
					+(System_T.ms-T.ms)/1000.0f
					+(Get_System_T().us-T.us)/1000000.0f;
}

/*
*@ Description :΢����ʱ
*@ param 1     :��ʱʱ��
*/
void delay_us(uint32_t nus)
{
	Time Last_T=Get_System_T();
	while((Get_deta_T(Last_T))<=nus/1000000.0f);
}
	
/*
*@ Description :������ʱ
*@ param 1     :��ʱʱ��
*/
void delay_ms(uint16_t nms)
{
 	Time Last_T=Get_System_T();
	while((Get_deta_T(Last_T))<=nms/1000.0f);
}


