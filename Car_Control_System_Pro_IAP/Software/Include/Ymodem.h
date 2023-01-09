#ifndef __Ymodem_H
#define __Ymodem_H

#include "gd32f30x_usart.h"
#include "System_time.h"
#include "usart_drv.h"
#include "Flash_drv.h"
#include "RingBuffer.h"
#include <string.h>



#define ApplicationAddress 	(0x8007800)//bootloder使用30Kb的flsah空间
//#define PAGE_SIZE           (0x800)//falsh的扇区大小
#define FLASH_SIZE 					(0x80000-0x7800)//flash剩余大小


#define REPASS  (-1)    //重传
#define FIAILED ( 0)    //接收失败
#define FINISH  (-2)    //接收完成
#define CATCH   ( 1)    //继续接收


#define PACKET_SEQNO_INDEX      (1)                 // 数据包序号索引
#define PACKET_SEQNO_COMP_INDEX (2)									// 数据包序列编码索引

#define PACKET_HEADER           (3)                     // 数据包头大小
#define PACKET_TRAILER          (2)                     // 数据尾巴大小
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

