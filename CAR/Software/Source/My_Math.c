#include "My_Math.h"








//float My_absf(float num)
//{
//	if(num<0)
//		return -num;
//	return num;
//}

/**
*@Description :�����������ֵ
*@param       :��������
*@return      :����ֵ����
**/
float My_absf(float num)
{
	union
	{
		float  a;  
		uint32_t b;
	}Temp ;//���� uint32 ת����ͬ��
	
	Temp.a = num;
	Temp.b&=0xefffffff;
	return Temp.a;
}




