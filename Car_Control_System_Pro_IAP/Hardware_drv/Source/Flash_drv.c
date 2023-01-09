#include "Flash_drv.h"







uint8_t Flash_Erase(uint32_t First_address,uint32_t size)
{
	fmc_unlock();     
	fmc_state_enum FLASHStatus = FMC_READY;
	if(size > Flash_SIZE-(First_address-0x8000000))
	{
		fmc_lock(); 
		return 0;
	}
	int i,Erases_num=size/PAGE_SIZE;
	if(size%PAGE_SIZE!=0)
		Erases_num++;
	for(i=0;(i<Erases_num)&&((FLASHStatus == FMC_READY));i++)
	{
		FLASHStatus = fmc_page_erase(First_address + (PAGE_SIZE * i));  
	}
	fmc_lock(); 
	return 1;
}


uint8_t Flash_Write(uint32_t Write_address,uint8_t *data,uint16_t Write_num)
{
	uint16_t i;
	if((Write_address<0x8000000) || Write_address>=(Flash_SIZE+0x8000000))
		return 0;
	fmc_unlock();     
	for(i=0;i<Write_num;i+=4)
	{
		while(1)
		{
			if (*(uint32_t*)(Write_address+i) != *(uint32_t*)(data+i))       
			{
				fmc_word_program(Write_address+i, *(uint32_t*)(data+i));		
				delay_us(100);
			}else
			{
				break;                                                              
			}
		}
	}
	fmc_lock(); 
	return 1;
}

void Flash_Read(uint32_t Read_address,uint8_t *data,uint16_t Read_num)
{
	uint16_t i;
	for(i=0;i<Read_num;i++)
	{
		*(data+i) = *(uint8_t*)(Read_address+i);
	}
}