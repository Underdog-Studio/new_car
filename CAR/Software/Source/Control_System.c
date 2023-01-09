#include "Control_System.h"




//�����
#define Motor_Control_Task_STK_SIZE			256
TaskHandle_t Motor_Control_Task_Handler;
void Motor_Control_Task(void *pvParameters);
//�����
#define Attitude_Control_Task_STK_SIZE			128
TaskHandle_t Attitude_Control_Task_Handler;
void Attitude_Control_Task(void *pvParameters);

static uint8_t Control_System_Switch=DISABLE;//DISABLE;//����������
static uint8_t IMU_Statu;
volatile PID_Type Yaw_Contrl_PID;


volatile float Mn_Target_Vel[4] = {0,0,0,0}, //�����
			 Mn_Observation_Vel[4] = {0,0,0,0}, //�����
			 Mn_Mileage[4] = {0,0,0,0},    //�����
			 Vel_Y=0,Vel_X=0,Vel_Yaw=0;    //�����

/**
*@Description :�����
**/
void Control_System_Init(void)
{
	Motor_Control_Init();
	IMU_Statu=Get_IMU_Status();

	xTaskCreate((TaskFunction_t		)Motor_Control_Task,
						(const char*			)"Motor_Control_Task",
						(uint16_t					)Motor_Control_Task_STK_SIZE,
						(void*						)NULL,
						(UBaseType_t			)Motor_Control_Task_PRIO,
						(TaskHandle_t*		)&Motor_Control_Task_Handler);//�����
	xTaskCreate((TaskFunction_t		)Attitude_Control_Task,
						(const char*			)"Attitude_Control_Task",
						(uint16_t					)Attitude_Control_Task_STK_SIZE,
						(void*						)NULL,
						(UBaseType_t			)Attitude_Control_Task_PRIO,
						(TaskHandle_t*		)&Attitude_Control_Task_Handler);//�����

}
	
/*
*@Description :�����
*/
void Attitude_Control_Task(void *pvParameters)
{
	while (1)
	{
		if(Control_System_Switch==ENABLE)
		{
			if(IMU_Statu)
			{
				Yaw_Contrl_PID.Observed = -Get_Primeval_Gyr().z;
				Yaw_Contrl_PID.Target   = Vel_Yaw;
				PID_Positional_Calculate(&Yaw_Contrl_PID);
				
				Mn_Target_Vel[0]= -(Vel_Y+Vel_X-Yaw_Contrl_PID.PID_Out);
				Mn_Target_Vel[1]= -(Vel_Y-Vel_X-Yaw_Contrl_PID.PID_Out);
				Mn_Target_Vel[2]=   Vel_Y+Vel_X+Yaw_Contrl_PID.PID_Out;
				Mn_Target_Vel[3]=   Vel_Y-Vel_X+Yaw_Contrl_PID.PID_Out;
			}else
			{
				Mn_Target_Vel[0]=-(Vel_Y+Vel_X-Vel_Yaw);
				Mn_Target_Vel[1]=-(Vel_Y-Vel_X-Vel_Yaw);
				Mn_Target_Vel[2]= (Vel_Y+Vel_X+Vel_Yaw);
				Mn_Target_Vel[3]= (Vel_Y-Vel_X+Vel_Yaw);
			}
			
		}
		vTaskDelay(5);
	}
}

/*
*@Description :�����
*/
void Motor_Control_Task(void *pvParameters)
{
	Encoder_Type Motor_Encode;
	while (1)
	{
		Motor_Encode = Get_Timer_Pulse(T1);//�����
		Motor_Velocity_Control(M1,Mn_Observation_Vel[0],Mn_Target_Vel[0]);//�����(PID)
		Mn_Observation_Vel[0] = Motor_Factor / Motor_Encode.T * Motor_Encode.Pluse;
		Mn_Mileage[0] += Motor_Encode.Pluse * Motor_Factor;//�����

		Motor_Encode = Get_Timer_Pulse(T2);
		Mn_Observation_Vel[1] = Motor_Factor / Motor_Encode.T * Motor_Encode.Pluse;
		Motor_Velocity_Control(M2,Mn_Observation_Vel[1],Mn_Target_Vel[1]);
		Mn_Mileage[1] += Motor_Encode.Pluse * Motor_Factor;

		Motor_Encode = Get_Timer_Pulse(T3);
		Mn_Observation_Vel[2] = Motor_Factor / Motor_Encode.T * Motor_Encode.Pluse;
		Motor_Velocity_Control(M3,Mn_Observation_Vel[2],Mn_Target_Vel[2]);
		Mn_Mileage[2] += Motor_Encode.Pluse * Motor_Factor;

		Motor_Encode = Get_Timer_Pulse(T4);
		Mn_Observation_Vel[3] = Motor_Factor / Motor_Encode.T * Motor_Encode.Pluse;
		Motor_Velocity_Control(M4,Mn_Observation_Vel[3],Mn_Target_Vel[3]);
		Mn_Mileage[3] += Motor_Encode.Pluse * Motor_Factor;

		vTaskDelay(3);
	}
	
}

/**
*@Description :����� �����
*@param       :�����
**/
void Set_Yaw_PID(PID_Type PID_Temp)
{
	Yaw_Contrl_PID = PID_Temp;
}


/**
*@Description :����������
*@param       :�����
*@param       :�����
**/
void Set_Motor_Target_Vel(uint8_t Mn,float Vel)
{
	Mn_Target_Vel[Mn-1] = Vel;
}

/*
*@Description :����������
*@param       :�����
*@return      :�����
*/

float Get_Motor_Target_Vel(uint8_t Mn)
{
	return Mn_Target_Vel[Mn-1];
}

/**
*@Description :����������
*@param       :�����
*@return      :�����
**/
float Get_Motor_Observation_Vel(uint8_t Mn)
{
	return Mn_Observation_Vel[Mn-1];
}
/**
*@Description :�����
*@param       :�����
*@return      :�����
**/
float Get_Motor_Mileage(uint8_t Mn)
{
	return Mn_Mileage[Mn-1];
}


/**
*@Description :�����
*@param       :�����
**/
void Set_Body_X(float Vel)
{
	Vel_X = Vel;
}
/**
*@Description :�����
*@return      :�����
**/
float Get_Body_X(void)
{
	return Vel_X;
}
/**
*@Description :�����
*@param       :�����
**/
void Set_Body_Y(float Vel)
{
	Vel_Y = Vel;
}
/**
*@Description :�����
*@return      :�����
**/
float Get_Body_Y(void)
{
	return Vel_Y;
}
/**
*@Description :�����
*@param       :�����
**/
void Set_Body_Yaw(float Vel)
{
	Vel_Yaw = Vel;
}
/**
*@Description :�����
*@return      :�����
**/
float Get_Body_Yaw(void)
{
	return Vel_Yaw;
}




void Control_System_Enable(void)
{
	Control_System_Switch = ENABLE;
}
void Control_System_Disable(void)
{
	Control_System_Switch = DISABLE;
}
uint8_t Get_Control_Switch(void)
{
	return Control_System_Switch;
}
