#include "Solution_System.h"
#include "arm_math.h"

static Attitude Att_Var;//:??????????
Three_axes Primeval_Acc,Primeval_Gyr,Primeval_Mag;
Three_axes _30HZ_LPF_Acc;
Three_axes Gyr_Off;//:??????????
static float Servo_Pos[4]={0.0f,0.0f,0.0f,0.0f};
void Attitude_Solution(Three_axes Gyr,Three_axes Acc,Three_axes Mag);//:??????????
/**
*@Description ::??????????
**/
void Solution_System_Init(void)
{
  //:??????????
	Att_Var.Roll=0;
	Att_Var.Pitch=0;
	Att_Var.Yaw=0;
	Att_Var.SinRoll=0;
	Att_Var.SinPitch=0;
	Att_Var.SinYaw=0;
	Att_Var.CosRoll=0;
	Att_Var.CosPitch=0;
	Att_Var.CosYaw=0;
	Att_Var.Att_Q.q0=1;
	Att_Var.Att_Q.q1=0;
	Att_Var.Att_Q.q2=0;
	Att_Var.Att_Q.q3=0;
	
}

/**
*@Description ::??????????:??????????:??????????
**/
extern Butter_Parameter Butter_30HZ_Parameter_Acce;
Butter_BufferData Accx_BufferData,Accy_BufferData,Accz_BufferData;
Three_axes Lase_Gyr,Gyr_title;
void Solution_System(void)
{
	Time Solution_T;

	//ICM_Get_Accelerometer(&Primeval_Acc);//??????????
	// _30HZ_LPF_Acc.x = LPButterworth(Primeval_Acc.x,&Accx_BufferData,&Butter_30HZ_Parameter_Acce);
	// _30HZ_LPF_Acc.y = LPButterworth(Primeval_Acc.y,&Accy_BufferData,&Butter_30HZ_Parameter_Acce);
	// _30HZ_LPF_Acc.z = LPButterworth(Primeval_Acc.z,&Accz_BufferData,&Butter_30HZ_Parameter_Acce);
	ICM_Get_Gyroscope(&Primeval_Gyr);//?????????
	
	Gyr_title.x = Primeval_Gyr.x - Lase_Gyr.x;
	Gyr_title.y = Primeval_Gyr.y - Lase_Gyr.y;
	Gyr_title.z = Primeval_Gyr.z - Lase_Gyr.z;
	
	Lase_Gyr=Primeval_Gyr;
	
	// {
	//IST_Get_Geomagnetism(&Primeval_Mag);//??????
	// }
	
	// Servo_Pos[0] = (float)get_adc_value(0);//??????
	// Servo_Pos[1] = (float)get_adc_value(1);
	// Servo_Pos[2] = (float)get_adc_value(2);
	// Servo_Pos[3] = (float)get_adc_value(3);
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	// Attitude_Solution(Primeval_Gyr,_30HZ_LPF_Acc,Primeval_Gyr);//?????????
}

/*
*@ Description ?????????
*@ param ??????
*@ return ??????
*/
float InvSqrt(float x)
{
	float halfx = 0.5f*x;
	float y=x;
	long i = *(long*)&y;
	i=0x5f3759df-(i>>1);
	y=*(float*)&i;
	y=y*(1.5f-(halfx*y*y));
	return y;
}

/**
*@Description :?????????
*@param       :??????
*@param       :???
*@param       :?????????
**/
void Attitude_Solution(Three_axes Gyr,Three_axes Acc,Three_axes Mag)
{
	Three_axes Norm_Gyr; 
	float Delta=0,Factor=0,Attitude_Solution_Interval_T=Get_deta_T(Att_Var.Last_T);//???
	float _2q0, _2q1, _2q2, _2q3, _4q0, _4q1, _4q2 ,_4q3 ,_8q1, _8q2, q0q0, q1q1, q2q2, q3q3;
	float Dq0,Dq1,Dq2,Dq3;//???
	float Sq0,Sq1,Sq2,Sq3;
	float sinroll,sinpitch;
	Att_Var.Last_T=Get_System_T();
	//??????
	Norm_Gyr.x= Gyr.x*Norm_Radian;
	Norm_Gyr.y= Gyr.y*Norm_Radian;
	Norm_Gyr.z=-Gyr.z*Norm_Radian;
	
	/*???*/
	Dq0 = 0.5f*(-Att_Var.Att_Q.q1*Norm_Gyr.x - Att_Var.Att_Q.q2*Norm_Gyr.y - Att_Var.Att_Q.q3*Norm_Gyr.z);//0.5*(-q1*Gx - q2*Gy - q3*Gz)
	Dq1 = 0.5f*( Att_Var.Att_Q.q0*Norm_Gyr.x + Att_Var.Att_Q.q2*Norm_Gyr.z - Att_Var.Att_Q.q3*Norm_Gyr.y);//0.5*( q0*Gx + q2*Gz - q3*Gy) 
	Dq2 = 0.5f*( Att_Var.Att_Q.q0*Norm_Gyr.y - Att_Var.Att_Q.q1*Norm_Gyr.z + Att_Var.Att_Q.q3*Norm_Gyr.x);//0.5*( q0*Gy - q1*Gz + q3*Gx)
	Dq3 = 0.5f*( Att_Var.Att_Q.q0*Norm_Gyr.z + Att_Var.Att_Q.q1*Norm_Gyr.y - Att_Var.Att_Q.q2*Norm_Gyr.x);//0.5*( q0*Gz + q1*Gy - q2*Gx)
	
	/*??????*/
	if(!(Acc.x==0.0f && Acc.y == 0.0f && Acc.z == 0.0f))
	{
		/*??????*/
		Att_Var.Acc_Length = Acc.x*Acc.x+Acc.y*Acc.y+Acc.z*Acc.z;
		/*??????*/
//		Factor = InvSqrt(Att_Var.Acc_Length);
//		Acc.x *= Factor;
//		Acc.y *= Factor;
//		Acc.z *= Factor;
			arm_sqrt_f32(Att_Var.Acc_Length,&Factor);
	   	Acc.x /= Factor;
		  Acc.y /= Factor;
   		Acc.z /= Factor;
		/* ????????? */
		_2q0 = 2.0f * Att_Var.Att_Q.q0;
		_2q1 = 2.0f * Att_Var.Att_Q.q1;
		_2q2 = 2.0f * Att_Var.Att_Q.q2;
		_2q3 = 2.0f * Att_Var.Att_Q.q3;
		_4q0 = 4.0f * Att_Var.Att_Q.q0;
		_4q1 = 4.0f * Att_Var.Att_Q.q1;
		_4q2 = 4.0f * Att_Var.Att_Q.q2;
		_4q3 = 4.0f * Att_Var.Att_Q.q3;
		_8q1 = 8.0f * Att_Var.Att_Q.q1;
		_8q2 = 8.0f * Att_Var.Att_Q.q2;
		q0q0 = Att_Var.Att_Q.q0 * Att_Var.Att_Q.q0;
		q1q1 = Att_Var.Att_Q.q1 * Att_Var.Att_Q.q1;
		q2q2 = Att_Var.Att_Q.q2 * Att_Var.Att_Q.q2;
		q3q3 = Att_Var.Att_Q.q3 * Att_Var.Att_Q.q3;
		
		/*?????????*/
		Sq0 = _4q0*q2q2 + _2q2*Acc.x + _4q0*q1q1 - _2q1*Acc.y;                                               //Sq0 = 4q0q2q2 + 2q2 ax + 4q0q1q1 - 2q1 ay
		Sq1 = _4q1*q3q3 - _2q3*Acc.x + _4q1*q0q0 - _2q0*Acc.y - _4q1 + _8q1*q1q1 + _8q1*q2q2 + _4q1*Acc.z;	 //Sq1 = 4q1q3q3 - 2q3 ax + 4q1q0q0 - 2q0 ay - 4q1 + 8q1q1q1 + 8q1q2q2 + 4q1 az
		Sq2 = _4q2*q0q0 + _2q0*Acc.x + _4q2*q3q3 - _2q3*Acc.y - _4q2 + _8q2*q1q1 + _8q2*q2q2 + _4q2*Acc.z;   //Sq2 = 4q2q0q0 + 2q0 ax + 4q2q3q3 - 2q3 ay - 4q2 + 8q2q1q1 + 8q2q2q2 + 4q2 az
		Sq3 = _4q3*q1q1 - _2q1*Acc.x + _4q3*q2q2 - _2q2*Acc.y;																							 //Sq3 = 4q3q1q1 - 2q1 ax + 4q3q2q2 - 2q2 ay
		
		/*??????*/
		arm_sqrt_f32(Sq0*Sq0+Sq1*Sq1+Sq2*Sq2+Sq3*Sq3,&Factor);
		Sq0 /= Factor;
		Sq1 /= Factor;
		Sq2 /= Factor;
		Sq3 /= Factor;
		
		/*?????????*/
		float BETADEF = 0.002f;//93
		Dq0 -= BETADEF*Sq0;
		Dq1 -= BETADEF*Sq1;
		Dq2 -= BETADEF*Sq2;
		Dq3 -= BETADEF*Sq3;
		
	}
	
	/*??????*/
	Delta=(Attitude_Solution_Interval_T*Norm_Gyr.x)*(Attitude_Solution_Interval_T*Norm_Gyr.x)
				+(Attitude_Solution_Interval_T*Norm_Gyr.y)*(Attitude_Solution_Interval_T*Norm_Gyr.y)
				+(Attitude_Solution_Interval_T*Norm_Gyr.z)*(Attitude_Solution_Interval_T*Norm_Gyr.z);
	Att_Var.Att_Q.q0 = (1.0f - Attitude_Solution_Interval_T / 8.0f)*Att_Var.Att_Q.q0 + Dq0*Attitude_Solution_Interval_T;  //q0 = (1-T/8)*q0 + Dq0*T
	Att_Var.Att_Q.q1 = (1.0f - Attitude_Solution_Interval_T / 8.0f)*Att_Var.Att_Q.q1 + Dq1*Attitude_Solution_Interval_T;  //q1 = (1-T/8)*q1 + Dq1*T
	Att_Var.Att_Q.q2 = (1.0f - Attitude_Solution_Interval_T / 8.0f)*Att_Var.Att_Q.q2 + Dq2*Attitude_Solution_Interval_T;  //q2 = (1-T/8)*q2 + Dq2*T
	Att_Var.Att_Q.q3 = (1.0f - Attitude_Solution_Interval_T / 8.0f)*Att_Var.Att_Q.q3 + Dq3*Attitude_Solution_Interval_T;  //q3 = (1-T/8)*q3 + Dq3*T

	/*?????????*/
	arm_sqrt_f32(Att_Var.Att_Q.q0*Att_Var.Att_Q.q0 
							+Att_Var.Att_Q.q1*Att_Var.Att_Q.q1
							+Att_Var.Att_Q.q2*Att_Var.Att_Q.q2
							+Att_Var.Att_Q.q3*Att_Var.Att_Q.q3,&Factor);
	Att_Var.Att_Q.q0 /= Factor;	
	Att_Var.Att_Q.q1 /= Factor;
	Att_Var.Att_Q.q2 /= Factor;
	Att_Var.Att_Q.q3 /= Factor;
	
	
	
	Att_Var.Roll = asin(2.0f*(Att_Var.Att_Q.q0*Att_Var.Att_Q.q2 - Att_Var.Att_Q.q1*Att_Var.Att_Q.q3))*Norm_Angle; //ROLL  = arcsin(2*(q0*q2-q1*q3))*(弧度转角度系数)
	Att_Var.Pitch= asin(2.0f*(Att_Var.Att_Q.q0*Att_Var.Att_Q.q1 + Att_Var.Att_Q.q2*Att_Var.Att_Q.q3))*Norm_Angle; //Pitch = arcsin(2*(q0*q1+Q2*q3))*(弧度转角度系数)
	Att_Var.Yaw  = asin(2.0f*(Att_Var.Att_Q.q1*Att_Var.Att_Q.q2 + Att_Var.Att_Q.q0*Att_Var.Att_Q.q3))*Norm_Angle; 
	
	Att_Var.SinPitch = sinf(Att_Var.Pitch/Norm_Angle);
  Att_Var.SinRoll = sinf(Att_Var.Roll/Norm_Angle);
	Att_Var.CosPitch = cosf(Att_Var.Pitch/Norm_Angle);
  Att_Var.CosRoll = cosf(Att_Var.Roll/Norm_Angle);
	
	//arm_sin_cos_f32(Att_Var.Pitch,&(Att_Var.SinPitch),&(Att_Var.CosPitch));
	
//	Att_Var.Roll = atan2(-Acc.x,Acc.z)*Norm_Angle; 
//	Att_Var.Pitch = atan2(Acc.y,Acc.z)*Norm_Angle; 
	
//	Att_Var.Roll += (atan2(-Acc.x,Acc.z)*Norm_Angle-Att_Var.Roll); 
//	Att_Var.Pitch += (atan2(Acc.y,Acc.z)*Norm_Angle-Att_Var.Pitch); 
	
	
}

/**
*@Description :?????????
*@param       :???
**/
void Set_Gyr_Offsets(Three_axes Gyr_Offsets)
{
	Gyr_Off = Gyr_Offsets;
}



/**
*@Description :?????????
*@param       :???
*@return      :???
**/
float Get_Servo_Pos(uint8_t Sn)
{
	return Servo_Pos[Sn-1];
}
/**
*@Description :??????
*@return      :???
**/
Three_axes Get_Primeval_Acc(void)
{
  return Primeval_Acc;
}
/**
*@Description :??????
*@return      :???
**/
Three_axes Get__30HZ_LPF_Acc(void)
{
  return _30HZ_LPF_Acc;
}


/**
*@Description :??????
*@return      :?????????
**/
Three_axes Get_Primeval_Gyr(void)
{
	return Primeval_Gyr;
}
/**
*@Description :???
*@return      :???
**/
Three_axes Get_Primeval_Mag(void)
{
	return Primeval_Mag;
}
Attitude Get_Attitude(void)
{
	return Att_Var;
}
/**
*@Description :?????????
*@return      :???
**/
Three_axes Get_Geographic_Mag(void)
{
	Three_axes Geographic_Mag;
	Geographic_Mag.x = Primeval_Mag.x*Att_Var.CosPitch+6*Primeval_Mag.z*Att_Var.SinPitch;
	Geographic_Mag.y = Primeval_Mag.x*Att_Var.SinRoll*Att_Var.SinPitch + Primeval_Mag.y*Att_Var.CosRoll + 6.5*Primeval_Mag.z*Att_Var.SinRoll*Att_Var.CosPitch;
	Geographic_Mag.z = atan(Geographic_Mag.x/Geographic_Mag.y)*Norm_Angle;
	return Geographic_Mag;
}

