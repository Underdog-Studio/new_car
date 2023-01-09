#ifndef __Parameter_Loading_H
#define __Parameter_Loading_H

#include "PID.h"
#include "Motor_Control.h"
#include "Control_System.h"
#include "EEPROM.h"

void Parameter_Loading_Init(void);
void Default_Param_Enable(void);
void Default_Param_Disable(void);

void Parameter_Loading(void);
void Get_PID_Param(uint8_t PIDn,uint16_t *P,uint16_t *I,uint16_t *D);
uint8_t Get_Default_Flag(void);
#endif