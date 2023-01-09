#include "Manual_Control.h"

#define Manual_Control_STK_SIZE			256
TaskHandle_t Manual_Control_Task_Handler;
void Manual_Control_Mainfunc(void *pvParameters);

void Manual_Control_init(void)
{
    xTaskCreate((TaskFunction_t		)Manual_Control_Mainfunc,
                (const char*			)"Manual_Control_Mainfunc",
                (uint16_t					)Manual_Control_STK_SIZE,
                (void*						)NULL,
                (UBaseType_t			)Manual_Control_TASK_PRIO,
                (TaskHandle_t*		)&Manual_Control_Task_Handler);//�����
}

extern int16_t ReciveCH[];
void Manual_Control_Mainfunc(void *pvParameters)
{
    while (1)
    {
        if(Get_Control_Switch()==ENABLE)
        {
                if(ReciveCH[1] > 50 || ReciveCH[1] < -50)
                {
                    Set_Body_X(ReciveCH[1]/10);
                }else
                {
                    Set_Body_X(0);
                }
                if(ReciveCH[0] > 50 || ReciveCH[0] < -50)
                {
                    Set_Body_Y(ReciveCH[0]/10);
                }else
                {
                    Set_Body_Y(0);
                }                       
                if(ReciveCH[2] > 50 || ReciveCH[2] < -50)
                {
                    Set_Body_Yaw(-ReciveCH[2]/2);
                }else
                {
                    Set_Body_Yaw(0);
                }
            
        }
        vTaskDelay(15);  
    }
    
}

