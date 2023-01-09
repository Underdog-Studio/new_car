#include "Servo.h"

float Servo_Factor=0;

void Servo_Init(void)
{
	Servo_Factor = (Servo_Max_T-Servo_Min_T)/Servo_Max_Angle;
}


float Servo_Pos_Solution(float adc_Value)
{
	
}

void Servo_Pos_Control(uint8_t Sn,float Servo_Target_Pos)
{
	switch(Sn)
	{
		case 1:
			Set_PWM_Duty(PWME,(Servo_Min_T+Servo_Target_Pos*Servo_Factor)/0.2f);
		break;
		case 2:
			Set_PWM_Duty(PWMF,(Servo_Min_T+Servo_Target_Pos*Servo_Factor)/0.2f);
		break;
		case 3:
			Set_PWM_Duty(PWMG,(Servo_Min_T+Servo_Target_Pos*Servo_Factor)/0.2f);
		break;
		case 4:
			Set_PWM_Duty(PWMH,(Servo_Min_T+Servo_Target_Pos*Servo_Factor)/0.2f);
		break;
	}
}















