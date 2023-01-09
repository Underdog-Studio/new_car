#include "Button.h"


SemaphoreHandle_t Button_A,Button_B;
void Button_A_Callback(void);
void Button_B_Callback(void);
/**
*@Description :??????????
**/
void Button_Init(void)
{
    Button_A = xSemaphoreCreateBinary();
	Button_B = xSemaphoreCreateBinary();
	EXTI5_Callback_Register(Button_B_Callback);
	EXTI11_Callback_Register(Button_A_Callback);
}
/**
*@Description :??????????
**/
void Button_A_Callback(void)
{
	BaseType_t err;
	err = xSemaphoreGiveFromISR(Button_A,pdFALSE);
}

/**
*@Description :??????????
**/
void Button_B_Callback(void)
{
	BaseType_t err;
	err = xSemaphoreGiveFromISR(Button_B,pdFALSE);
}
/**
*@Description :??????????
*@param       :?????
**/
SemaphoreHandle_t Get_Button_SemapHore(uint8_t Button)
{
	if(Button == A)
	{
		return Button_A;
	}else
	{
		return Button_B;
	}
}












