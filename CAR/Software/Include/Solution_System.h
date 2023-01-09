#ifndef __Solution_System_H
#define __Solution_System_H

#include "Encoder_drv.h"
#include "adc_drv.h"
#include "IMU.h"
#include "math.h"
#include "Filter.h"

#define Houle_Pluse 28                    //?éœ?å?°”?è„?‰å?†²?æ•?
#define Decelerate_Ratio 50				  //å‡?é?€?Ÿæ?¯”?
#define Whell_Radius 2.4f                 //è½?¦è?½®?ç›?´å?¾„?
#define Motor_Factor 2*Pi_Radian*Whell_Radius/(Decelerate_Ratio*Houle_Pluse)


#define Pi_Radian 3.14159265f             //å¼?§å?º¦?P?I
#define Pi_Angle 180.0f					  //è§?’å?º¦?PI
#define Norm_Radian   Pi_Radian/Pi_Angle  //è§?’å?º¦?è½?¬å?¼§?åº?
#define Norm_Angle    Pi_Angle/Pi_Radian  //å¼?§å?º¦?è½?¬è§’åº??

typedef struct
{
	float q0;
	float q1;
	float q2;
	float q3;
}Quaternions;//å›?›å?…ƒ?æ•?

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
}Attitude;//å§?¿æ??€?æ?•°?æ?

//è§?£ç?®—?ç³?»ç?»Ÿ?åˆ?å?§‹?åŒ?
void Solution_System_Init(void);
void Solution_System(void);

//èˆ?µæ?œº?
float Get_Servo_Pos(uint8_t Sn);

//IMUæ•?°æ?®?
Three_axes Get_Primeval_Acc(void);
Three_axes Get_Primeval_Gyr(void);
Three_axes Get_Primeval_Mag(void);

Three_axes Get__30HZ_LPF_Acc(void);
Three_axes Get_Geographic_Mag(void);


void Set_Gyr_Offsets(Three_axes Gyr_Offsets);
Attitude Get_Attitude(void);



#endif
