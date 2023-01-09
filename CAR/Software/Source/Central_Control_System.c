#include "Central_Control_System.h"


#define Central_Control_System_Task_STK_SIZE			128
TaskHandle_t Central_Control_System_Task_Handler;
void Central_Control_System(void *pvParameters);


/*!
*@Description �����
*/
void Central_Control_System_Init(void)
{
	Solution_System_Init();//�����
	Control_System_Init();//�����
	Execute_System_Init();//�����
	
	xTaskCreate((TaskFunction_t		)Central_Control_System,
						(const char*			)"Central_Control_System",
						(uint16_t					)Central_Control_System_Task_STK_SIZE,
						(void*						)NULL,
						(UBaseType_t			)Central_Control_System_Task_PRIO,
						(TaskHandle_t*		)&Central_Control_System_Task_Handler);//����������



	
}




void Central_Control_System(void *pvParameters)
{
	
	while(1)
	{
		Solution_System();
		//Execute_System();
		
		vTaskDelay(5);
	}
}







