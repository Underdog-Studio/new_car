#include "Recive_Device.h"

#define Recive_Device_STK_SIZE			256
TaskHandle_t Recive_Device_Task_Handler;
void Recive_Device_Mainfunc(void *pvParameters);

int16_t ReciveCH[4];

void Recive_Device_USART_Callback_Register(uint8_t data);
ringBuffer_t Recive_Device_Buffer;
void Recive_Device_Init(void)
{
    usart4_init(115200);
    RingBuffer_Init(&Recive_Device_Buffer);
    USART4_IRQ_Callback_Register(Recive_Device_USART_Callback_Register);

	xTaskCreate((TaskFunction_t		)Recive_Device_Mainfunc,
					(const char*			)"Recive_Device_Mainfunc",
					(uint16_t					)Recive_Device_STK_SIZE,
					(void*						)NULL,
					(UBaseType_t			)Recive_Device_TASK_PRIO,
					(TaskHandle_t*		)&Recive_Device_Task_Handler);//�����

}

void Recive_Device_USART_Callback_Register(uint8_t data)
{
    RingBuffer_Write(&Recive_Device_Buffer,&data);
}


void Recive_Device_Mainfunc(void *pvParameters)
{
    uint8_t temp,recive_count=0,Recive_temp[8],SumA=0,SumB=0;
    while (1)
    {
        while (RingBuffer_Read(&Recive_Device_Buffer,&temp))
        {
            switch (recive_count)
            {
            case 0:
                if(temp == 0xAB)
                    recive_count++;
                break;
            case 1:
                if(temp == 0xBA)
                {
                    recive_count++;
                    SumA = 0;
                    SumB = 0;
                }
                else
                    recive_count = 0;
                break;
            case 2:
            case 3:
            case 4:
            case 5:
            case 6:
            case 7:
            case 8:
            case 9:
                Recive_temp[recive_count - 2] = temp;
                SumA += temp;
                SumB += SumA;
                recive_count++;
                break;
            case 10:
                if(temp == SumA)
                    recive_count++;
                else
                    recive_count = 0;
                break;
            case 11:
                if(temp == SumB)
                {
                    ReciveCH[0] = *(int16_t*)Recive_temp;
                    ReciveCH[1] = *(int16_t*)(Recive_temp+2);
                    ReciveCH[2] = *(int16_t*)(Recive_temp+4);
                    ReciveCH[3] = *(int16_t*)(Recive_temp+6);
                }
                recive_count = 0;
                break;
            default:
                break;
            }
        }
        vTaskDelay(10);  
    }
}
