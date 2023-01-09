#include "Motor_Control.h"
static void Motor_DIR_GPIO_Init(void);


volatile PID_Type M1_PID,M2_PID,M3_PID,M4_PID;//�����

/**
*@Description :�����
**/
gpio_control DIR1,DIR2,DIR3,DIR4;
void Motor_Control_Init(void)
{
	DIR1 = get_gpio_struct(0);
	DIR2 = get_gpio_struct(1);
	DIR3 = get_gpio_struct(2);
	DIR4 = get_gpio_struct(3);
}

/**
*@Description :�����
*@param       :�����
*@param       :�����
**/
void Set_Motor_Pwm(uint8_t Mn,float Duty)
{
	switch(Mn)
	{
		case M1:
			Duty>=0?(DIR1.GPIO_HIGH(),Set_PWM_Duty(PWMA,Duty)):(DIR1.GPIO_LOW(),Set_PWM_Duty(PWMA,-(Duty)));
		break;
		case M2:
			Duty>=0?(DIR2.GPIO_HIGH(),Set_PWM_Duty(PWMB,Duty)):(DIR2.GPIO_LOW(),Set_PWM_Duty(PWMB,-(Duty)));
		break;
		case M3:
			Duty>=0?(DIR3.GPIO_HIGH(),Set_PWM_Duty(PWMC,Duty)):(DIR3.GPIO_LOW(),Set_PWM_Duty(PWMC,-(Duty)));
		break;
		case M4:
			Duty>=0?(DIR4.GPIO_HIGH(),Set_PWM_Duty(PWMD,Duty)):(DIR4.GPIO_LOW(),Set_PWM_Duty(PWMD,-(Duty)));
		break;
	}
}
/**
*@Description :�����
*@param       :�����
*@param       :�����
*@param       :�����
**/
extern Butter_Parameter Butter_30HZ_Parameter_Acce;
Butter_BufferData M1_BufferData,M2_BufferData,M3_BufferData,M4_BufferData;
void Motor_Velocity_Control(uint8_t Mn,float Observed_Vel,float Target_Vel)
{
	float temp1;
	switch(Mn)
	{
		case M1:
			M1_PID.Observed = Observed_Vel;//�����
			M1_PID.Target = Target_Vel;//�����
			PID_Positional_Calculate(&M1_PID);
			Set_Motor_Pwm(M1,M1_PID.PID_Out);//�����
		break;
		case M2:
			M2_PID.Observed = Observed_Vel;
			M2_PID.Target = Target_Vel;
			PID_Positional_Calculate(&M2_PID);
			Set_Motor_Pwm(M2,M2_PID.PID_Out);
		break;
		case M3:
			M3_PID.Observed = Observed_Vel;
			M3_PID.Target = Target_Vel;
			PID_Positional_Calculate(&M3_PID);
		    Set_Motor_Pwm(M3,M3_PID.PID_Out);
		break;
		case M4:
			M4_PID.Observed = Observed_Vel;
			M4_PID.Target = Target_Vel;
			PID_Positional_Calculate(&M4_PID);
		    Set_Motor_Pwm(M4,M4_PID.PID_Out);
		break;
	}
}

/**
*@Description :����������
*@param       :�����
*@param       :�����
**/
void Set_Motor_PID(uint8_t Mn,PID_Type PID_Temp)
{
	switch(Mn)
	{
		case M1:
			M1_PID = PID_Temp;
		break;
		case M2:
			M2_PID = PID_Temp;
		break;
	  case M3:
			M3_PID = PID_Temp;
		break;
		case M4:
			M4_PID = PID_Temp;
		break;
	}
}

/*
*@Description :����������
*@param       :�����
*@return      :�����
*/
PID_Type Get_Motor_PID(uint8_t Mn)
{
	switch(Mn)
	{
		case M1:
			return M1_PID;
		case M2:
			return M2_PID;
	  	case M3:
			return M3_PID;
		case M4:
			return M4_PID;
		default:
			return M4_PID;
	} 
}
