#include "gd32f30x_it.h"

#include "ws2812_drv.h"
#include "System_time.h"
#include "FreeRTOS.h"
#include "task.h"
#include "Task_Priority.h"

#include "Encoder_drv.h"
#include "gpio_drv.h"
#include "Software_I2C.h"
#include "I2C_drv.h"
#include "EXTI_drv.h"
#include "adc_drv.h"

#include "Servo.h"
#include "Button.h"
#include "BUZZER.h"
#include "EEPROM.h"
#include "IMU.h"
#include "pwm_drv.h"
#include "ANO_TC.h"
#include "UDPI_Connect.h"
#include "Central_Control_System.h"
#include "Execute_System.h"
#include "Recive_Device.h"
#include "Parameter_Loading.h"
#include "Manual_Control.h"

#include "Digital_Signature.h"

#include "arm_math.h"

extern ws2812_byte ws2812;


#define Car_System_Init_Task_STK_SIZE			128
TaskHandle_t Car_System_Init_Task_Handler;
void Car_System_Init_Task(void *pvParameters);

int main(void)
{
	nvic_priority_group_set(NVIC_PRIGROUP_PRE4_SUB0);//éæ¤æ·éæ¤æ·éæ¤æ·éé¥ºç¡·æ·éæ¤æ·éæ¤æ·2
	rcu_periph_clock_enable(RCU_AF);
	rcu_periph_clock_enable(RCU_GPIOA);
	rcu_periph_clock_enable(RCU_GPIOB);
	rcu_periph_clock_enable(RCU_GPIOC);
	rcu_periph_clock_enable(RCU_GPIOD);
	rcu_periph_clock_enable(RCU_GPIOE);
	rcu_periph_clock_enable(RCU_GPIOF);
	System_time_init();
	xTaskCreate((TaskFunction_t		)Car_System_Init_Task,
				(const char*	)"Car_System_Init_Task",
				(uint16_t		)Car_System_Init_Task_STK_SIZE,
				(void*			)NULL,
				(UBaseType_t	)Car_System_Init_Task_PRIO,
				(TaskHandle_t*  )&Car_System_Init_Task_Handler);//éæ¤æ·éæ¤æ·å°éæ¤æ·éæ¤æ·å§éæ¤æ·éæ¤æ·éæ¤æ·
	vTaskStartScheduler();
	while(1)
	{

	}
}





#define WS2812_Task_STK_SIZE			128
TaskHandle_t WS2812_Task_Handler;
void WS2812_Task(void *pvParameters);


#define BUZZER_Task_STK_SIZE			128
TaskHandle_t BUZZER_Task_Handler;
void BUZZER_Task(void *pvParameters);


void Car_System_Init_Task(void *pvParameters)
{
	EEPROM_Init();
	Positive_Check();//æ­ç ¡é
	pwm_init();//PWM
	ws2812_Init();
	Encoder_Init();//ç¼ç å¨
    all_gpio_init();//GPIO
	adc_init();
	EXTI_Init();
	Button_Init();
	I2C_Init();
	BUZZER_Init();
	Parameter_Loading_Init();
	IMU_Init();//IMU
  	Servo_Init();
	Recive_Device_Init();//æ¥æ¶æº
	Manual_Control_init();//æå¨æ§å¶

	Central_Control_System_Init();//ä¸­æ§ç³»ç»
	
	ANO_Init();//å¿åå°é¢ç«
	
    //UDPI_Connect_Init();
	xTaskCreate((TaskFunction_t		)WS2812_Task,
							(const char*			)"WS2812_Task",
							(uint16_t					)WS2812_Task_STK_SIZE,
							(void*						)NULL,
							(UBaseType_t			)WS2812_Task_PRIO,
							(TaskHandle_t*		)&WS2812_Task_Handler);
	xTaskCreate((TaskFunction_t		)BUZZER_Task,
							(const char*			)"BUZZER_Task",
							(uint16_t					)BUZZER_Task_STK_SIZE,
							(void*						)NULL,
							(UBaseType_t			)BUZZER_Task_PRIO,
							(TaskHandle_t*		)&BUZZER_Task_Handler);
		//å éæ¤æ·éæ¤æ·éæ¤æ·éæ¤æ·
	vTaskDelete(0);
}

void WS2812_Task(void *pvParameters)
{
	uint16_t Color_R=255,Color_G=0,Color_B=0,i=0,RGB = 255;
	uint16_t LED_T=4;
	SemaphoreHandle_t Button_A = Get_Button_SemapHore(A);
	SemaphoreHandle_t Button_B = Get_Button_SemapHore(B);
	while(1)
	{
		for(i=0;i<RGB;i++)
		{
			Color_R--;
			Color_G++;
			ws2812_Control(Color_R,Color_G,Color_B);
			vTaskDelay(LED_T);
		}
		Color_R=0;
		for(i=0;i<RGB;i++)
		{
			Color_G--;
			Color_B++;
			ws2812_Control(Color_R,Color_G,Color_B);
			vTaskDelay(LED_T);
		}
		Color_G=0;
		for(i=0;i<RGB;i++)
		{
			Color_B--;
			Color_R++;
			ws2812_Control(Color_R,Color_G,Color_B);
			vTaskDelay(LED_T);
		}
		Color_B=0;

	}
	
}

void BUZZER_Task(void *pvParameters)
{
	uint16_t R=200,G=0,i=0,RGB = 0,adc_temp[4];
	uint16_t LED_T=5;
	SemaphoreHandle_t Button_A = Get_Button_SemapHore(A);
	SemaphoreHandle_t Button_B = Get_Button_SemapHore(B);
	while(1)
	{
		if(xSemaphoreTake(Button_A,0)==pdTRUE)
		{
			if(Get_Control_Switch()==ENABLE)
				Control_System_Disable();
			else
				Control_System_Enable();
			Set_Buzzer(256,LED_T);
			vTaskDelay(100);
			Set_Buzzer(288,LED_T);
			vTaskDelay(100);
			Set_Buzzer(320,LED_T);
			vTaskDelay(100);
			Set_Buzzer(341,LED_T);
			vTaskDelay(100);
			Set_Buzzer(384,LED_T);
			vTaskDelay(100);
			Set_Buzzer(426,LED_T);
			vTaskDelay(100);
			Set_Buzzer(480,LED_T);
			vTaskDelay(100);
			Set_Buzzer(512,LED_T);
			vTaskDelay(100);
			Buzzer_Disable();

		    Set_Buzzer(512,LED_T);
		    vTaskDelay(100);
			Set_Buzzer(480,LED_T);
			vTaskDelay(100);
			Set_Buzzer(426,LED_T);
			vTaskDelay(100);
			Set_Buzzer(384,LED_T);
			vTaskDelay(100);
			Set_Buzzer(341,LED_T);
			vTaskDelay(100);
			Set_Buzzer(320,LED_T);
			vTaskDelay(100);
			Set_Buzzer(288,LED_T);
			vTaskDelay(100);
			Set_Buzzer(256,LED_T);
			vTaskDelay(100);
			Buzzer_Disable();

		}
		vTaskDelay(100);
	}
	
}
