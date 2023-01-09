#ifndef __UDPI_Connect_H
#define __UDPI_Connect_H

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "Task_Priority.h"
#include "Execute_System.h"


#include "RingBuffer.h"

#include "usart_drv.h"

#define UDPI_X_Axis   0x01  //�?��?��?X?�?��?��?�?
#define UDPI_Y_Axis   0x02  //�?��?��?�?��?��?�?
#define UDPI_Yaw_Axis 0x03  //控�?��?Y?a?w?�?�移�??
#define UDPI_Servo    0x04  //�?��?��?�?��?��?�?��?��

#define Get_Version   0x0f  //?�?��?��?�?��?��?�?��?��?�?��?��
#define Get_Move      0x1f  //�?��?��?�?��?��?�?��?��?�?��?��
#define Get_Servo     0x2f  //�?��?��?�?��?��?�?��?��?�?��?��
#define Get_State     0x3f  //�?��?��?�?��?��?�?��?�?


typedef struct 
{
    int16_t Distance;
    int16_t Velocity;
    int16_t Acceleration;
}UDPI_Move_data;//�?��?��?�?��?��

typedef struct 
{
    uint8_t X_Axis;
    uint8_t Y_Axis;
    uint8_t Yaw_Axis;
}UDPI_state_data;//�?��?�?��?��?�?


void UDPI_Connect_Init(void);









#endif

