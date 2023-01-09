#ifndef __Solution_System_H
#define __Solution_System_H

#include "Encoder_drv.h"
#include "adc_drv.h"
#include "IMU.h"
#include "math.h"
#include "Filter.h"

#define Houle_Pluse 28                    //?�?��?��?�?��?��?�?
#define Decelerate_Ratio 50				  //�?��?�?��?��?
#define Whell_Radius 2.4f                 //�?��?��?�?��?��?
#define Motor_Factor 2*Pi_Radian*Whell_Radius/(Decelerate_Ratio*Houle_Pluse)


#define Pi_Radian 3.14159265f             //�?��?��?P?I
#define Pi_Angle 180.0f					  //�?��?��?PI
#define Norm_Radian   Pi_Radian/Pi_Angle  //�?��?��?�?��?��?�?
#define Norm_Angle    Pi_Angle/Pi_Radian  //�?��?��?�?�角�??

typedef struct
{
	float q0;
	float q1;
	float q2;
	float q3;
}Quaternions;//�?��?��?�?

typedef struct
{
	float Roll;
	float Pitch;
	float Yaw;
	float SinRoll;
	float CosRoll;
	float SinPitch;
	float CosPitch;
	float SinYaw;
	float CosYaw;
	Quaternions Att_Q;
	Time Last_T;
	float Acc_Length;
}Attitude;//�?��??�?��?��?�?

//�?��?��?�?��?��?�?��?��?�?
void Solution_System_Init(void);
void Solution_System(void);

//�?��?��?
float Get_Servo_Pos(uint8_t Sn);

//IMU�?��?��?
Three_axes Get_Primeval_Acc(void);
Three_axes Get_Primeval_Gyr(void);
Three_axes Get_Primeval_Mag(void);

Three_axes Get__30HZ_LPF_Acc(void);
Three_axes Get_Geographic_Mag(void);


void Set_Gyr_Offsets(Three_axes Gyr_Offsets);
Attitude Get_Attitude(void);



#endif
