#include "Digital_Signature.h"

bool Positive_Check_State = FALSE;




//�����
void Positive_Check(void)
{
	uint32_t Check1,Check2,Check3;
	uint8_t Secret_Key[12]={'u','n','d','e','r','d','o','g','7','8','9','9'};
	
	uint32_t ID1 = *(uint32_t *)(0x1FFFF7E8);        //UNIQUE_ID[31: 0]
	uint32_t ID2 = *(uint32_t *)(0x1FFFF7EC);        //UNIQUE_ID[63:32]
	uint32_t ID3 = *(uint32_t *)(0x1FFFF7F0);        //UNIQUE_ID[95:63]
	
	Check1=((ID1>>1)|(ID2&0x01))^ID1;
	Check2=((ID2>>1)|(ID3&0x01))^ID2;
	Check3=((ID3>>1)|(ID1&0x01))^ID3;
	
	
	Check1^=(uint32_t)Secret_Key[0];
	Check2^=(uint32_t)Secret_Key[4];
	Check3^=(uint32_t)Secret_Key[8];
	
	Check1=~Check1;
	Check2=~Check2;
	Check3=~Check3;
	
	EEPROM_WriteOneWord(0,Check1);
	EEPROM_WriteOneWord(4,Check2);
	EEPROM_WriteOneWord(8,Check3);

	EEPROM_WriteOneWord(12,0X01030101);//�����
	EEPROM_Data_Save();
	

    ws2812_Control(255,0,0);
	while(1)
 	{
		
	 	if(Check1==EEPROM_ReadOneWord(0))
		{
			if(Check2==EEPROM_ReadOneWord(4))
			{
				if(Check3==EEPROM_ReadOneWord(8))
				{
					Positive_Check_State = TRUE;
					break;
				}
			}
		}
		vTaskDelay(100);
	}
	

	
}

/**
*@Description �����
*@return      �����
**/
bool Get_Positive_Check_State(void)
{
	return Positive_Check_State;
}

void Registered_Device(uint32_t Check1,uint32_t Check2,uint32_t Check3)
{
	EEPROM_WriteOneWord(0,Check1);
	EEPROM_WriteOneWord(4,Check2);
	EEPROM_WriteOneWord(8,Check3);
	EEPROM_Data_Save();
	
	
	uint8_t Secret_Key[12]={'u','n','d','e','r','d','o','g','7','8','9','9'};
	
	uint32_t ID1 = *(uint32_t *)(0x1FFFF7E8);        //UNIQUE_ID[31: 0]
    uint32_t ID2 = *(uint32_t *)(0x1FFFF7EC);        //UNIQUE_ID[63:32]
    uint32_t ID3 = *(uint32_t *)(0x1FFFF7F0);        //UNIQUE_ID[95:63]
	
	Check1=((ID1>>1)|(ID2&0x01))^ID1;
	Check2=((ID2>>1)|(ID3&0x01))^ID2;
	Check3=((ID3>>1)|(ID1&0x01))^ID3;
	
	
	Check1^=(uint32_t)Secret_Key[0];
	Check2^=(uint32_t)Secret_Key[4];
	Check3^=(uint32_t)Secret_Key[8];
	
	Check1=~Check1;
	Check2=~Check2;
	Check3=~Check3;
	Positive_Check_State = FALSE;
	if(Check1==EEPROM_ReadOneWord(0))
	{
		if(Check2==EEPROM_ReadOneWord(4))
		{
			if(Check3==EEPROM_ReadOneWord(8))
			{
				Positive_Check_State = TRUE;
			}
		}
	}
}


