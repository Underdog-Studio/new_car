#include "gd32f30x.h"
#include "System_time.h"
#include "ws2812_drv.h"
#include "usart_drv.h"
#include "gpio_drv.h"
#include "Ymodem.h"

Time Main_T;

typedef  void (*pFunction)(void);
pFunction Jump_To_Application;
uint32_t JumpAddress;
uint8_t Go_to_APP(void);

int main(void)
{
	gpio_control Button_A,Button_B;
	nvic_priority_group_set(NVIC_PRIGROUP_PRE4_SUB0);//设置优先级分组2
	rcu_periph_clock_enable(RCU_AF);
	rcu_periph_clock_enable(RCU_GPIOA);
	rcu_periph_clock_enable(RCU_GPIOB);
	rcu_periph_clock_enable(RCU_GPIOC);
	rcu_periph_clock_enable(RCU_GPIOD);
	rcu_periph_clock_enable(RCU_GPIOE);
	rcu_periph_clock_enable(RCU_GPIOF);
	System_time_init();
	ws2812_Init();
	
	all_gpio_init();
	usart2_init(115200);
	Ymodem_init();
	Button_A = get_gpio_struct(0);
	Button_B = get_gpio_struct(1);
	Main_T=Get_System_T();
	if(Button_A.GPIO_GET() == SET)
	{
		while(1)
		{
			if(Get_deta_T(Main_T)>0.3)
			{
				usart2_send_byte('C');
				Main_T=Get_System_T();
			}
			if(Get_System_T().ms>500)
			{
				ws2812_Control(255,0,0);
			}else
			{
				ws2812_Control(0,0,255);
			}
			if(Get_Connecting())
			{
				ws2812_Control(255,0,0);
				if(~Ymodem_Receive())//更新固件
				{
					ws2812_Control(0,0,0);
					Go_to_APP();
				}
			}
		}
	}else
		{
			Go_to_APP();
		}
}

static uint8_t Go_to_APP(void)
{
	if (((*(__IO uint32_t*)ApplicationAddress) & 0x2FFE0000 ) == 0x20000000)
  { 
		JumpAddress = *(__IO uint32_t*) (ApplicationAddress + 4);  //ResetHander的地址偏移
		Jump_To_Application = (pFunction) JumpAddress;
		__set_MSP(*(__IO uint32_t*) ApplicationAddress); //指向栈顶
		
		for(int i = 0; i < 8; i++) 
		{
			NVIC->ICER[i] = 0xFFFFFFFF; // 关闭中断
      NVIC->ICPR[i] = 0xFFFFFFFF; // 清除中断标志位
    }
		rcu_deinit();
		SysTick->CTRL = 0;
    SysTick->LOAD = 0;
    SysTick->VAL = 0;
		Jump_To_Application();													 //跳转到APP
  }
	return 0;
}

