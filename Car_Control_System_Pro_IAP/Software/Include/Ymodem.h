#ifndef __Ymodem_H
#define __Ymodem_H

#include "gd32f30x_usart.h"
#include "System_time.h"
#include "usart_drv.h"
#include "Flash_drv.h"
#include "RingBuffer.h"
#include <string.h>



#define ApplicationAddress 	(0x8007800)//bootloderʹ��30Kb��flsah�ռ�
//#define PAGE_SIZE           (0x800)//falsh��������С
#define FLASH_SIZE 					(0x80000-0x7800)//flashʣ���С


#define REPASS  (-1)    //�ش�
#define FIAILED ( 0)    //����ʧ��
#define FINISH  (-2)    //�������
#define CATCH   ( 1)    //��������


#define PACKET_SEQNO_INDEX      (1)                 // ���ݰ��������
#define PACKET_SEQNO_COMP_INDEX (2)									// ���ݰ����б�������

#define PACKET_HEADER           (3)                     // ���ݰ�ͷ��С
#define PACKET_TRAILER          (2)                     // ����β�ʹ�С
#define PACKET_OVERHEAD         (PACKET_HEADER + PACKET_TRAILER)
#define PACKET_128b_SIZE        (128)
#define PACKET_1K_SIZE          (1024)


#define SOH                     (0x01)  /* start of 128-byte data packet */
#define STX                     (0x02)  /* start of 1024-byte data packet */
#define EOT                     (0x04)  /* end of transmission */
#define ACK                     (0x06)  /* acknowledge */
#define NAK                     (0x15)  /* negative acknowledge */
#define CA                      (0x18)  /* two of these in succession aborts transfer */
#define CC                      (0x43)  /* 'C' == 0x43, request 16-bit CRC */

void Ymodem_init(void);
char Ymodem_Receive(void);
uint8_t Get_Connecting(void);
#endif

