#include "Execute_System.h"

enum Move_State
{
	Accelerate=1, //加速
	Decelerate=2, //减速
	Unifrom=3,    //匀速
	Stop=4        //停止
};


typedef struct
{
	uint8_t State;
	Time    T;
	float Distance;
	float Acc;
	float Acc_Target_Vel;//加速目标值
	float Dec_Target_Vel;//减速目标值
	float Now_Distance;
	float Now_Vel;
	float Decelerate_Distance;
}Move_Control_Type;


Move_Control_Type Move_Control[7];

Time MM_T;

/*!
*@Description :执行系统初始化
*/
void Execute_System_Init(void)
{
	MM_T = Get_System_T();
	Move_Control[0].Now_Vel = 0;
	Move_Control[0].State = Stop;
	Move_Control[1].Now_Vel = 0;
	Move_Control[1].State = Stop;
	Move_Control[2].Now_Vel = 0;
	Move_Control[2].State = Stop;
}

/*!
*@Description :执行系统
*/
int16_t iii=0;
uint8_t ttt=0;
Time Exe_T;
void Execute_System(void)
{
	uint8_t i;
	for(i=0;i<3;i++)
	{
		switch(Move_Control[i].State)
		{
			case Accelerate://加速
				Move_Control[i].Now_Distance += Move_Control[i].Now_Vel*Get_deta_T(Move_Control[i].T);//已走路程
				if(Move_Control[i].Now_Vel <= Move_Control[i].Acc_Target_Vel)//速度小于目标速度--加速
				{
					Move_Control[i].Now_Vel += Move_Control[i].Acc * Get_deta_T(Move_Control[i].T);
				}else
				{
					if(Move_Control[i].Acc_Target_Vel != 0)//有目标加速到速度
					{
						Move_Control[i].Now_Vel = Move_Control[i].Acc_Target_Vel;
						Move_Control[i].State = Unifrom;//切换匀速
					}
					else
					{
						Move_Control[i].Now_Vel = 0;
						Move_Control[i].State   = Stop;//速度为0 切换停止
					}
				}
				Move_Control[i].T = Get_System_T();//跟新时间
			break;
			case Decelerate://减速
				Move_Control[i].Now_Distance += Move_Control[i].Now_Vel*Get_deta_T(Move_Control[i].T);//已走路程
				if(Move_Control[i].Now_Vel > Move_Control[i].Dec_Target_Vel)
				{
					Move_Control[i].Now_Vel -= Move_Control[i].Acc*Get_deta_T(Move_Control[i].T);
				}else
				{
						if(Move_Control[i].Dec_Target_Vel == 0)
						{
							Move_Control[i].Now_Vel = 0;
							Move_Control[i].State   = Stop;//速度为0 切换停止
						}
						else
						{
							Move_Control[i].Now_Vel = Move_Control[i].Dec_Target_Vel;
							Move_Control[i].State   =Unifrom;//切换匀速
						}
				}
				Move_Control[i].T = Get_System_T();//跟新时间
			break;
			case Unifrom://匀速
				Move_Control[i].Now_Distance += Move_Control[i].Now_Vel*Get_deta_T(Move_Control[i].T);//已走路程
				if((fabs(Move_Control[i].Now_Distance)>=fabs(Move_Control[i].Decelerate_Distance)) && (Move_Control[i].Distance!=0))//到达开始减速位置且路程不为0
				{
					if(Move_Control[i].Dec_Target_Vel == 0)
						Move_Control[i].State = Decelerate;
					if(Move_Control[i].Acc_Target_Vel == 0)
						Move_Control[i].State = Accelerate;
				}
				Move_Control[i].T = Get_System_T();//跟新时间
			break;
			case Stop:
				Move_Control[i].T = Get_System_T();//�����
			break;
		}
		switch(i)
		{
			case 0:
				Set_Body_Y(Move_Control[0].Now_Vel);
			break;
			case 1:
				Set_Body_X(Move_Control[1].Now_Vel);
			break;
			case 2:
				Set_Body_Yaw(Move_Control[2].Now_Vel);
			break;
//			case 3:
//				Servo_Pos_Control(1,Move_Control[3].Now_Distance);
//			break;
//			case 4:
//				Servo_Pos_Control(2,Move_Control[4].Now_Distance);
//			break;
//			case 5:
//				Servo_Pos_Control(3,Move_Control[5].Now_Distance);
//			break;
//			case 6:
//				Servo_Pos_Control(4,Move_Control[6].Now_Distance);
//			break;
		}
		
	}
	for(i=0;i<3;i++)
	{
		
		
		
	}
}

/**
*@Description :����������
*@param       :����� 
*@param       :�����
*@param       :�����
*@return      :�����
**/
uint8_t Set_Move(uint8_t n,int16_t h,int16_t Vel,int16_t acc)
{
	  float Vel_Max=0,Target_Vel=0,Temp_Distance=0;  //�����  �����
		if(h==0)
		{
			Move_Control[n].Distance = 0;//�����
			if(Move_Control[n].Now_Vel > Vel)//����������
			{
				Move_Control[n].Dec_Target_Vel = (float)Vel;//�����
				Move_Control[n].State = Decelerate;//�����
			}else if(Move_Control[n].Now_Vel < Vel)//����������
			{
				Move_Control[n].Acc_Target_Vel = (float)Vel;//�����
				Move_Control[n].State = Accelerate;//�����
			}
			Move_Control[n].Acc = (float)acc;//�����
			arm_abs_f32(&(Move_Control[n].Acc),&(Move_Control[n].Acc),1);//����������
			Move_Control[n].T = Get_System_T();
		}else if(Move_Control[n].State == Stop)//�����
		{
			Move_Control[n].Distance = (float)h;  //�����
			Target_Vel = (float)Vel;
			arm_abs_f32(&Target_Vel,&Target_Vel,1);//����������
			Move_Control[n].Acc = (float)acc;
			arm_abs_f32(&(Move_Control[n].Acc),&(Move_Control[n].Acc),1);//����������
			Move_Control[n].Now_Distance = 0;//�����
			
			arm_abs_f32(&(Move_Control[n].Distance),&Temp_Distance,1);//����������
			arm_sqrt_f32(2*Move_Control[n].Acc*(Temp_Distance/2)+Move_Control[n].Now_Vel*Move_Control[n].Now_Vel,&Vel_Max);//����������
			if(Target_Vel > Vel_Max)//����� �����
			{
				Target_Vel = Vel_Max;
			}	
			
			if(Move_Control[n].Distance > 0)//����� �����
			{
				if(Move_Control[n].Now_Vel<Target_Vel)
				{
					Move_Control[n].Acc_Target_Vel = Target_Vel;
					Move_Control[n].Dec_Target_Vel = 0;
					Move_Control[n].State = Accelerate; //�����
				}
				else if(Move_Control[n].Now_Vel>Target_Vel)
				{
					Move_Control[n].Acc_Target_Vel = 0;
					Move_Control[n].Dec_Target_Vel = Target_Vel;
					Move_Control[n].State = Decelerate; //�����
				}
			}else//����� �����
			{
				if(Move_Control[n].Now_Vel < -Target_Vel)
				{
					Move_Control[n].Acc_Target_Vel = -Target_Vel;
					Move_Control[n].Dec_Target_Vel = 0;
					Move_Control[n].State = Accelerate; //�����
				}
				else if(Move_Control[n].Now_Vel>-Target_Vel)
				{
					Move_Control[n].Acc_Target_Vel = 0;
					Move_Control[n].Dec_Target_Vel = -Target_Vel;
					Move_Control[n].State = Decelerate; //�����
				}
			}
			Move_Control[n].Decelerate_Distance = Temp_Distance - Target_Vel*Target_Vel/(float)(2*Move_Control[n].Acc); //�����
			Move_Control[n].T = Get_System_T();
			return 1;			
		}else
		{
			return 0;
		}
}

int16_t Get_X_Body_Vel(void)
{
	return Move_Control[1].Now_Vel;
}

int16_t Get_Y_Body_Vel(void)
{
	return Move_Control[0].Now_Vel;
}

int16_t Get_Yaw_Body_Vel(void)
{
	return Move_Control[2].Now_Vel;
}

uint8_t Get_X_State(void)
{
	return Move_Control[1].State;
}

uint8_t Get_Y_State(void)
{
	return Move_Control[0].State;
}

uint8_t Get_Yaw_State(void)
{
	return Move_Control[2].State;
}
