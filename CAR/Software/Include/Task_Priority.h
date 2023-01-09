#ifndef __Task_Priority_H
#define __Task_Priority_H





#define Car_System_Init_Task_PRIO			1

#define UDPI_TASK_PRIO			         9    //10ms
#define Recive_Device_TASK_PRIO			 10   //10ms
#define Manual_Control_TASK_PRIO          11   //15ms
#define HC_TASK_PRIO			         12   //50ms
#define ANO_TC_TASK_PRIO			     12   //50ms

#define BUZZER_Task_PRIO			     33   //100ms
#define WS2812_Task_PRIO			     34   //~~LED_T

#define Motor_Control_Task_PRIO          5//3ms
#define Attitude_Control_Task_PRIO       7//5ms
#define Central_Control_System_Task_PRIO 6   //3ms
#endif
