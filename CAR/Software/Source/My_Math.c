#include "My_Math.h"








//float My_absf(float num)
//{
//	if(num<0)
//		return -num;
//	return num;
//}

/**
*@Description :浮点型求绝对值
*@param       :待求数据
*@return      :绝对值数据
**/
float My_absf(float num)
{
	union
	{
		float  a;  
		uint32_t b;
	}Temp ;//浮点 uint32 转换共同体
	
	Temp.a = num;
	Temp.b&=0xefffffff;
	return Temp.a;
}




