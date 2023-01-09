#ifndef __Digital_Signature_H
#define __Digital_Signature_H

#include "gd32f30x.h"
#include "EEPROM.h"
#include "System_time.h"
#include "ws2812_drv.h"


//Õý°æ¼ì²â
void Positive_Check(void);

bool Get_Positive_Check_State(void);

void Registered_Device(uint32_t Check1,uint32_t Check2,uint32_t Check3);




#endif

