#ifndef __UDPI_Connect_H
#define __UDPI_Connect_H

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "Task_Priority.h"
#include "Execute_System.h"


#include "RingBuffer.h"

#include "usart_drv.h"

#define UDPI_X_Axis   0x01  //æ?§å?ˆ¶?X?è½?´ç?§»?åŠ?
#define UDPI_Y_Axis   0x02  //æ?§å?ˆ¶?è½?´ç?§»?åŠ?
#define UDPI_Yaw_Axis 0x03  //æ§å?ˆ¶?Y?a?w?è½?´ç§»åŠ??
#define UDPI_Servo    0x04  //æ?§å?ˆ¶?èˆ?µæ?œº?è§?’å?º¦

#define Get_Version   0x0f  //?è?·å?–?å°?è?½¦?ç‰?ˆæ?œ¬?ä¿?¡æ?¯
#define Get_Move      0x1f  //è?·å?–?æœ?ºä?½“?ç§?»å?Š¨?æ•?°æ?®
#define Get_Servo     0x2f  //è?·å?–?èˆ?µæ?œº?è½?¬å?Š¨?æ•?°æ?®
#define Get_State     0x3f  //è?·å?–?å°?è?½¦?çŠ?¶æ?€?


typedef struct 
{
    int16_t Distance;
    int16_t Velocity;
    int16_t Acceleration;
}UDPI_Move_data;//ç§?»å?Š¨?æ•?°æ?®

typedef struct 
{
    uint8_t X_Axis;
    uint8_t Y_Axis;
    uint8_t Yaw_Axis;
}UDPI_state_data;//çŠ?¶æ?€?æ?•°?æ?


void UDPI_Connect_Init(void);









#endif

