#include "EEPROM.h"

static uint8_t EEPROM_Data[2048];
//AT24C08 ����� �����*�����

union
{float  a;  
	uint32_t b;
}Temp ;//����� uint32 �����

/**
*@Description :�����
**/
void EEPROM_Init(void)
{
	EEPROM_Updata();
}

/**
*@Description :����������
*@param       :�����
*@param       :�����
**/
void EEPROM_WriteOneByte(uint8_t WriteAddr,uint8_t data)
{
	*(uint8_t*)(&EEPROM_Data[WriteAddr]) = data;
}
/**
*@Description :���������� 
*@param       :�����
*@return      :�����
**/
uint8_t EEPROM_ReadOneByte(uint16_t ReadAddr)
{
	uint8_t temp;
	Flash_Read(0x3F800+ReadAddr,(uint8_t*)(&temp),1);
	return temp;
}
/**
*@Description :����������
*@param       :�����
*@param       :�����
**/
void EEPROM_WriteOneHalfword(uint16_t WriteAddr,uint16_t data)
{
	*(uint16_t*)(&EEPROM_Data[WriteAddr]) = data;
}
/**
*@Description :���������� 
*@param       :�����
*@return      :�����
**/
uint16_t EEPROM_ReadOneHalfword(uint16_t ReadAddr)
{
	uint16_t temp;
	Flash_Read(0x3F800+ReadAddr,(uint8_t*)(&temp),2);
	return temp;
}

/**
*@Description :����� �����
*@param       :����� ����������(0-63) �����(0-15)
*@param       :�����
**/
void EEPROM_WriteOneWord(uint16_t WriteAddr,uint32_t data)
{
	*(uint32_t*)(&EEPROM_Data[WriteAddr]) = data;
}

/**
*@Description :����� 
*@param       :����� �����(0-63) �����(0-15)
*@return      :�����
**/
uint32_t EEPROM_ReadOneWord(uint16_t ReadAddr)
{
	uint32_t temp;
	Flash_Read(0x3F800+ReadAddr,(uint8_t*)(&temp),4);
	return temp;
}

/**
*@Description :����� 
*@param       :�����
*@return      :�����
**/
float EEPROM_Read_float(uint16_t ReadAddr)
{
	Flash_Read(0x3F800+ReadAddr,(uint8_t*)(&Temp.b),4);
	return Temp.a;
}

/**
*@Description :����� �����
*@param       :�����
*@param       :�����
**/
void EEPROM_Write_float(uint16_t WriteAddr,float data)
{
	Temp.a=data;
	*(uint32_t*)(&EEPROM_Data[WriteAddr]) = Temp.b;
}
/**
*@Description :�����
**/


void EEPROM_Data_Save(void)
{
	taskENTER_CRITICAL();
	Flash_Erase(0x803F800,2048);//�����
	Flash_Write(0x803F800,EEPROM_Data,2048);
	taskEXIT_CRITICAL();	
}
/**
*@Description :�����
**/
void EEPROM_Updata(void)
{
	Flash_Read(0x803F800,EEPROM_Data,2048);
}

/*
*@ Description �����
*@ param �����
*@ return �����
*/
//u8 Parameters_Loading(void)
//{
//	int16_t P,I,D;
//	P=EEPROM_ReadOneHalfword(0x0010);
//	I=EEPROM_ReadOneHalfword(0x0012);
//	D=EEPROM_ReadOneHalfword(0x0014);
//	Set_Motor_PID(M1,P,I,D);
//	P=EEPROM_ReadOneHalfword(0x0016);
//	I=EEPROM_ReadOneHalfword(0x0018);
//	D=EEPROM_ReadOneHalfword(0x001A);
//	Set_Motor_PID(M2,P,I,D);
//	P=EEPROM_ReadOneHalfword(0x001C);
//	I=EEPROM_ReadOneHalfword(0x001E);
//	D=EEPROM_ReadOneHalfword(0x0020);
//	Set_Motor_PID(M3,P,I,D);
//	P=EEPROM_ReadOneHalfword(0x0022);
//	I=EEPROM_ReadOneHalfword(0x0024);
//	D=EEPROM_ReadOneHalfword(0x0026);
//	Set_Motor_PID(M4,P,I,D);
//	P=EEPROM_ReadOneHalfword(0x0028);
//	I=EEPROM_ReadOneHalfword(0x002A);
//	D=EEPROM_ReadOneHalfword(0x002C);
//	//Set_Yaw_PID(P,I,D);
//}


