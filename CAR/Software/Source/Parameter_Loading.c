#include "Parameter_Loading.h"
//									  ?????  ?????  ?????  ?????  ?????      ?????      ?????
PID_Type Default_Param[5]={{0,0,0,0,0,100          ,-100         ,100            ,-100           ,1.5          ,1.0          ,0            ,0,0,0,0},//M1
						   {0,0,0,0,0,100          ,-100         ,100            ,-100           ,1.5          ,1.0          ,0            ,0,0,0,0},//M2
						   {0,0,0,0,0,100          ,-100         ,100            ,-100           ,1.5          ,1.0          ,0            ,0,0,0,0},//M3
						   {0,0,0,0,0,100          ,-100         ,100            ,-100           ,1.5          ,1.0          ,0            ,0,0,0,0},//M4
						   {0,0,0,0,0,100          ,-100         ,100            ,-100           ,0.1          ,0.01         ,0            ,0,0,0,0}};//Yaw

PID_Type PID_Param[5];											 

uint8_t Default_Param_Flag=0xf0;
void Parameter_Loading_Init(void)
{
	Default_Param_Flag = EEPROM_ReadOneByte(46);
	
	Parameter_Loading();
}

void Default_Param_Enable(void)
{
	EEPROM_WriteOneByte(46,0xf0);
	Default_Param_Flag=0xf0;
	EEPROM_Data_Save();
	Parameter_Loading();
}

void Default_Param_Disable(void)
{
	EEPROM_WriteOneByte(46,0x0f);
	Default_Param_Flag=0x0f;
	EEPROM_Data_Save();
	Parameter_Loading();
}

void Parameter_Loading(void)
{
	
	PID_Param[0] = Default_Param[0];
	if(Default_Param_Flag == 0x0f)
	{
		PID_Param[0].P = EEPROM_ReadOneHalfword(16)/100.0f;
		PID_Param[0].I = EEPROM_ReadOneHalfword(18)/100.0f;
		PID_Param[0].D = EEPROM_ReadOneHalfword(20)/100.0f;
	}
	Set_Motor_PID(M1,PID_Param[0]);
	
	PID_Param[1] = Default_Param[1];
	if(Default_Param_Flag == 0x0f)
	{
		PID_Param[1].P = EEPROM_ReadOneHalfword(22)/100.0f;
		PID_Param[1].I = EEPROM_ReadOneHalfword(24)/100.0f;
		PID_Param[1].D = EEPROM_ReadOneHalfword(26)/100.0f;
	}
	Set_Motor_PID(M2,PID_Param[1]);
	
	PID_Param[2] = Default_Param[2];
	if(Default_Param_Flag == 0x0f)
	{
		PID_Param[2].P = EEPROM_ReadOneHalfword(28)/100.0f;
		PID_Param[2].I = EEPROM_ReadOneHalfword(30)/100.0f;
		PID_Param[2].D = EEPROM_ReadOneHalfword(32)/100.0f;
	}
	Set_Motor_PID(M3,PID_Param[2]);
	
	PID_Param[3] = Default_Param[3];
	if(Default_Param_Flag == 0x0f)
	{
		PID_Param[3].P = EEPROM_ReadOneHalfword(34)/100.0f;
		PID_Param[3].I = EEPROM_ReadOneHalfword(36)/100.0f;
		PID_Param[3].D = EEPROM_ReadOneHalfword(38)/100.0f;
	}
	Set_Motor_PID(M4,PID_Param[3]);
	
	PID_Param[4] = Default_Param[4];
	if(Default_Param_Flag == 0x0f)
	{
		PID_Param[4].P = EEPROM_ReadOneHalfword(40)/100.0f;
		PID_Param[4].I = EEPROM_ReadOneHalfword(42)/100.0f;
		PID_Param[4].D = EEPROM_ReadOneHalfword(44)/100.0f;
	}
	Set_Yaw_PID(PID_Param[4]);
}

void Get_PID_Param(uint8_t PIDn,uint16_t *P,uint16_t *I,uint16_t *D)
{
	*P = PID_Param[PIDn].P*100.0f;
	*I = PID_Param[PIDn].I*100.0f;
	*D = PID_Param[PIDn].D*100.0f;
}

uint8_t Get_Default_Flag(void)
{
	return Default_Param_Flag;
}
