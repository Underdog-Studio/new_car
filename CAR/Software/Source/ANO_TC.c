#include "ANO_TC.h"



//�????��?�?��?��?�?��?��?�???????�?��?��?�?��?��?�??

#define ANO_TC_STK_SIZE			256
TaskHandle_t ANO_TC_Task_Handler;
void ANO_Mainfunc(void *pvParameters);

//QueueHandle_t xQueue_ANO_RX;
ringBuffer_t ANO_Data_Buffer;

static void ANT_TC_USART_Callback_Register(uint8_t data); //�?��?��?�?�受?�?��?��
static void ANO_Return_Check(uint8_t FREAM_HEAD,uint8_t CHECK_SUM); //�?��?��?�?��?��
static void ANO_Upload_PID(void); //�?��?��?PID
/**
*@Description :�?��?��?�?�面?�?��?��?�?��??��?
**/
void ANO_Init(void)
{
	
	usart2_init(115200);//�?��????�?��?��?�??0
	USART2_IRQ_Callback_Register(ANT_TC_USART_Callback_Register);//�?��?��?�?��?��?�?��?��?�?��?��?�?��?��?�?��?��
	//xQueue_ANO_RX = xQueueCreate(512,sizeof(uint8_t));//�?��?��?�?��?��?�?��?��
	RingBuffer_Init(&ANO_Data_Buffer);
	xTaskCreate((TaskFunction_t		)ANO_Mainfunc,
					(const char*			)"ANO_Mainfunc",
					(uint16_t					)ANO_TC_STK_SIZE,
					(void*						)NULL,
					(UBaseType_t			)ANO_TC_TASK_PRIO,
					(TaskHandle_t*		)&ANO_TC_Task_Handler);//�?��?��?�?��?��?�?��?��?�??�??�?��?��?�?��?��?�?
}

/**
*@Description :�?��?��?�?��?��?�?��?��?�?��?��
*@param       :�?��?��?�?��?��?�?��?��
**/
static void ANT_TC_USART_Callback_Register(uint8_t data)
{
	//xQueueSendFromISR(xQueue_ANO_RX,&data,0);//�?��??��?�?��?��Se?nd?�?��?��
	RingBuffer_Write(&ANO_Data_Buffer,&data);
}

/**
*@Description :�?��?��?�?��?��?�?��?��?�???��?�?��?��?�?
**/
//�?��?���?�收?�?��?��
uint8_t ANT_Receive_State=0,//�???��?���?�受?�?��?��?��
				ANO_Function=0xff,  //�?�能?�? �?��???�???0Xff
        ANO_Data_Len=0,     //�?��?��?�?��?�� �?��?��?�?��?��?�?��?
        ANO_Data_Receive_Len=0, //�?��?��?接�?��?数�?���?��?�� �?��?��?接受?�?
        ANO_Receive_Data[50];   //�?��?��?�?��?��?�?��?��?�?
uint16_t ANO_SUN=0; //�?��?��?�?
extern PID_Type M4_PID;
extern  Three_axes Gyr_title;
extern float Mn_Observation_Vel[4];
extern int16_t ReciveCH[4];
void ANO_Mainfunc(void *pvParameters)
{
	uint8_t temp;
    while(1)
	{
		//�?��?��?�?��?��
		ANO_Sensors_Type Sensor_data;
		ANO_Attitude_Type Attitude_data;
		ANO_User1_Type User_data;
		ANO_Control_Type ANO_RC_data;

		Three_axes Three_axes_Temp;
		
		Three_axes_Temp = Get__30HZ_LPF_Acc();//�?��??��?��
		Sensor_data.ACC_X = Gyr_title.x*100;
		Sensor_data.ACC_Y = Gyr_title.y*100;
		Sensor_data.ACC_Z = Gyr_title.z*100;
		
		Three_axes_Temp = Get_Primeval_Gyr();//�??�??��?��
		Sensor_data.GYR_X = Three_axes_Temp.x;
		Sensor_data.GYR_Y = Three_axes_Temp.y;
		Sensor_data.GYR_Z = Three_axes_Temp.z;
		
		Three_axes_Temp = Get_Primeval_Mag();//�?��????�?��?��
		Sensor_data.MAG_X = Three_axes_Temp.x;
		Sensor_data.MAG_Y = Three_axes_Temp.y;
		Sensor_data.MAG_Z = Three_axes_Temp.z;
		
		Attitude_data.ROL = Get_Attitude().Roll;//�?��?�?��???
		Attitude_data.PIT = Get_Attitude().Pitch;
		Attitude_data.YAW = Get_Attitude().Yaw;
		
		
		// User_data.M1_Speed=Get_Motor_Observation_Vel(1);//�?��?��?�?��?��?�?��?��?�?��?��
		// User_data.M2_Speed=Get_Motor_Observation_Vel(2);
		// User_data.M3_Speed=Get_Motor_Observation_Vel(3);
		// User_data.M4_Speed=Get_Motor_Observation_Vel(4);
		User_data.M1_Speed=Mn_Observation_Vel[0];//�?��?��?�?��?��?�?��?��?�?��?��
		User_data.M2_Speed=Mn_Observation_Vel[1];
		User_data.M3_Speed=Mn_Observation_Vel[2];
		User_data.M4_Speed=Mn_Observation_Vel[3];
		//User_data.Voltage_ADC = timer_counter_read(TIMER1);

		User_data.M1_PID_Expectations = Get_Motor_Target_Vel(1);//�?��?��?�?��?��?�????��?�?��?��
		User_data.M2_PID_Expectations = Get_Motor_Target_Vel(2);
		User_data.M3_PID_Expectations = Get_Motor_Target_Vel(3);
		User_data.M4_PID_Expectations = Get_Motor_Target_Vel(4);
		
		User_data.M1_PID_OUT = Get_Motor_PID(1).PID_Out;//�?��?��?�?��?��?PID�?��?��
		User_data.M2_PID_OUT = Get_Motor_PID(2).PID_Out;
		User_data.M3_PID_OUT = Get_Motor_PID(3).PID_Out;
		User_data.M4_PID_OUT = Get_Motor_PID(4).PID_Out;

		ANO_RC_data.AUX1 = (uint16_t)(ReciveCH[0]/2+1500);
		ANO_RC_data.AUX2 = (uint16_t)(ReciveCH[1]/2+1500);
		ANO_RC_data.AUX3 = (uint16_t)(ReciveCH[2]/2+1500);
		ANO_RC_data.AUX4 = (uint16_t)(ReciveCH[3]/2+1500);

		ANO_Uploading_data(ANO_Sensors,&Sensor_data);//�?��?��?�?��?��v�?��?��?�?
		ANO_Uploading_data(ANO_Attitude,&Attitude_data);//�?��?��?�?��?�?��?��?�?
		ANO_Uploading_data(ANO_USER_1,&User_data);//�?��?��?�?��?��?�?��?��?(?�?��?��?�?��?��?�?��?���?)
		ANO_Uploading_data(ANO_Control,&ANO_RC_data);
		
		while(RingBuffer_Read(&ANO_Data_Buffer,&temp))
		{
			switch(ANT_Receive_State)
			{
				case 0://�?��?��?�?�头1
					
					if(temp==0xaa)//?�?��?��?1?
					{
						ANO_SUN=0;
						ANT_Receive_State++;
						ANO_SUN+=temp;
					}
				break;
				case 1:
					if(temp==0xaf)//�?��?��?�?��?��?2?�????��?�?�确
					{
						ANT_Receive_State++;
						ANO_SUN+=temp;
					}
					else//�?��????�????��?�?��?��?�??
					{
						ANT_Receive_State=0; //�?��?��?�?�?�?
						ANO_SUN=0;           //�?��?��?�?��????�?��?��?�?
					}
				break;
				case 2:
					if(ANO_Function==0xff)//�?��?��?�????��?�?��?��?�?��?��
					{
						ANO_Function=temp;//�?��?��?�?��?��?�?
						ANT_Receive_State++;
						ANO_SUN+=temp;
					}else                 //�?��?��?�?��?��?�?��?��?�?
					{
						ANT_Receive_State=0;//�?��?��?开??�?
						ANO_Function=0xff;//�?��?��?�?��?��?�?��?���??
						ANO_SUN=0;//�?��?��?验�????�?��?��?�?
					}
				break;
				case 3:
					if(ANO_Data_Len==0)//�?��?��?�?��?��?�?��?��?长度?
					{
						ANO_Data_Len=temp;//�?��?��?�?��?��?�?��?��
						ANO_Data_Receive_Len = 0;
						ANT_Receive_State++;
						ANO_SUN+=temp;
					}else                 //�?��?��?�?��?��?�?��?��?�?��?��
					{
						ANT_Receive_State=0;
						ANO_Function=0xff;//�?��?��?�?��?��?�?��?��?�?
						ANO_Data_Len=0;//�?��?��?�?��?��?�?��?��?�?��?��
						ANO_SUN=0;//�?��?��?�?��????�?��?��?�?
					}
				break;
				case 4:
					ANO_Receive_Data[ANO_Data_Receive_Len++]=temp;//�?��?��?�?��?��?�?��?��?�?��?��
					if(ANO_Data_Receive_Len==(ANO_Data_Len+1))//?�?��?��?�?��??�?�?��?��?
					{
						ANO_Data_Receive_Len=0;
						
						if(ANO_Receive_Data[ANO_Data_Len]==(ANO_SUN%256))//�?��?��?�?
						{

							switch(ANO_Function)//�?��?��?解�?��?�?��?�� 开?�?��?��?�?��?��?�?
							{
								case ANO_CMD1://�?��?��?�??��?��1
									
								break;
								case ANO_CMD2://�?��?��?�?��?��2
									
									if(ANO_Receive_Data[0]==0x01)
									{
										ANO_Upload_PID();//�?��?��P?ID�?��?��
									}
								break;
								//�?��?��P?ID
								case ANO_PID1:
									
									ANO_Return_Check(ANO_PID1,ANO_SUN%256);
							
								break;
								case ANO_PID2:
									
									ANO_Return_Check(ANO_PID2,ANO_SUN%256);
								
								break;
								case ANO_PID3:
									
									ANO_Return_Check(ANO_PID3,ANO_SUN%256);
								
								break;
								case ANO_PID4:
									
									ANO_Return_Check(ANO_PID4,ANO_SUN%256);
								
								break;
								case ANO_PID5:
									
									EEPROM_WriteOneHalfword(16,((int16_t)ANO_Receive_Data[0]<<8)|ANO_Receive_Data[1]);
									EEPROM_WriteOneHalfword(18,((int16_t)ANO_Receive_Data[2]<<8)|ANO_Receive_Data[3]);
									EEPROM_WriteOneHalfword(20,((int16_t)ANO_Receive_Data[4]<<8)|ANO_Receive_Data[5]);
									
									EEPROM_WriteOneHalfword(22,((int16_t)ANO_Receive_Data[6]<<8)|ANO_Receive_Data[7]);
									EEPROM_WriteOneHalfword(24,((int16_t)ANO_Receive_Data[8]<<8)|ANO_Receive_Data[9]);
									EEPROM_WriteOneHalfword(26,((int16_t)ANO_Receive_Data[10]<<8)|ANO_Receive_Data[11]);
									
									EEPROM_WriteOneHalfword(28,((int16_t)ANO_Receive_Data[12]<<8)|ANO_Receive_Data[13]);
									EEPROM_WriteOneHalfword(30,((int16_t)ANO_Receive_Data[14]<<8)|ANO_Receive_Data[15]);
									EEPROM_WriteOneHalfword(32,((int16_t)ANO_Receive_Data[16]<<8)|ANO_Receive_Data[17]);
									ANO_Return_Check(ANO_PID5,ANO_SUN%256);
								break;
								case ANO_PID6:
									
									EEPROM_WriteOneHalfword(34,((int16_t)ANO_Receive_Data[0]<<8)|ANO_Receive_Data[1]);
									EEPROM_WriteOneHalfword(36,((int16_t)ANO_Receive_Data[2]<<8)|ANO_Receive_Data[3]);
									EEPROM_WriteOneHalfword(38,((int16_t)ANO_Receive_Data[4]<<8)|ANO_Receive_Data[5]);
									
									EEPROM_WriteOneHalfword(40,((int16_t)ANO_Receive_Data[6]<<8)|ANO_Receive_Data[7]);
									EEPROM_WriteOneHalfword(42,((int16_t)ANO_Receive_Data[8]<<8)|ANO_Receive_Data[9]);
									EEPROM_WriteOneHalfword(44,((int16_t)ANO_Receive_Data[10]<<8)|ANO_Receive_Data[11]);
								  
									ANO_Return_Check(ANO_PID6,ANO_SUN%256);
									EEPROM_Data_Save();
									Parameter_Loading();//�?��?��?�?��?��?�?��?��?
								break;
								default:
									ANO_Return_Check(ANO_Function,ANO_SUN%256);
									
								break;
							}
						}
						ANO_Function=0xff;//�?�新??��??���?�能??�?
						ANO_Data_Len=0;//�?��?��?�?��?��?�?��?��?�?��?��
						ANO_SUN=0;//�?��?��?�?��??��??��?��?�?
						ANT_Receive_State=0;//�?��?��?开�?
					}
					ANO_SUN+=temp;//�?��?��?�?��?��? �?��?��?�??最?�?��?��?�?��??验�?��?�?
				break;
			}
		}
		vTaskDelay(15);
	}
}




/*
*@ Description �?��?���?��?��?站�?��?传�?��?�?
*@ param �?��?��?类�?��(?�能??)
*@ param �?��?��?�?��?��?�?��?��
*@ return ?�?��?��?�???��?
*/
void ANO_Uploading_data(uint8_t type,void *data)
{
	uint8_t Temp_Data[100],i,j;
	switch(type)
	{
		case ANO_Attitude:
			Temp_Data[0]=0xAA;//??�???
			Temp_Data[1]=0xAA;//???????
			Temp_Data[2]=ANO_Attitude;//?�?��?��?类�?��?
			Temp_Data[3]=0x0C;//�?��?�??��?��?
			Temp_Data[4]=(uint8_t)(((int16_t)(100*(*(ANO_Attitude_Type*)data).ROL)&0xFF00)>>8);
			Temp_Data[5]=(uint8_t)(((int16_t)(100*(*(ANO_Attitude_Type*)data).ROL)&0x00FF)>>0);
			Temp_Data[6]=(uint8_t)(((int16_t)(100*(*(ANO_Attitude_Type*)data).PIT)&0xFF00)>>8);
			Temp_Data[7]=(uint8_t)(((int16_t)(100*(*(ANO_Attitude_Type*)data).PIT)&0x00FF)>>0);
			Temp_Data[8]=(uint8_t)(((int16_t)(100*(*(ANO_Attitude_Type*)data).YAW)&0xFF00)>>8);
			Temp_Data[9]=(uint8_t)(((int16_t)(100*(*(ANO_Attitude_Type*)data).YAW)&0x00FF)>>0);
			
			Temp_Data[10]=(uint8_t)(((int32_t)((*(ANO_Attitude_Type*)data).ALT_USE)&0xFF000000)>>24);
			Temp_Data[11]=(uint8_t)(((int32_t)((*(ANO_Attitude_Type*)data).ALT_USE)&0x00FF0000)>>16);
			Temp_Data[12]=(uint8_t)(((int32_t)((*(ANO_Attitude_Type*)data).ALT_USE)&0x0000FF00)>>8);
			Temp_Data[13]=(uint8_t)(((int32_t)((*(ANO_Attitude_Type*)data).ALT_USE)&0x000000FF)>>0);
			
			Temp_Data[14]=(uint8_t)(((*(ANO_Attitude_Type*)data).FLY_MODEL));
			Temp_Data[15]=(uint8_t)(((*(ANO_Attitude_Type*)data).ARMED));
		
			Temp_Data[16]=0;
			for(i=0;i<16;i++)
			{
				Temp_Data[16]+=Temp_Data[i];
			}
		break;
		case ANO_Sensors:
			Temp_Data[0]=0xAA;//?????
			Temp_Data[1]=0xAA;//?????
			Temp_Data[2]=ANO_Sensors;//?????
			Temp_Data[3]=0x12;//?????
			Temp_Data[4]=(uint8_t)(((int16_t)((*(ANO_Sensors_Type*)data).ACC_X)&0xFF00)>>8);
			Temp_Data[5]=(uint8_t)(((int16_t)((*(ANO_Sensors_Type*)data).ACC_X)&0x00FF)>>0);
			Temp_Data[6]=(uint8_t)(((int16_t)((*(ANO_Sensors_Type*)data).ACC_Y)&0xFF00)>>8);
			Temp_Data[7]=(uint8_t)(((int16_t)((*(ANO_Sensors_Type*)data).ACC_Y)&0x00FF)>>0);
			Temp_Data[8]=(uint8_t)(((int16_t)((*(ANO_Sensors_Type*)data).ACC_Z)&0xFF00)>>8);
			Temp_Data[9]=(uint8_t)(((int16_t)((*(ANO_Sensors_Type*)data).ACC_Z)&0x00FF)>>0);
			
			Temp_Data[10]=(uint8_t)(((int16_t)((*(ANO_Sensors_Type*)data).GYR_X)&0xFF00)>>8);
			Temp_Data[11]=(uint8_t)(((int16_t)((*(ANO_Sensors_Type*)data).GYR_X)&0x00FF)>>0);
			Temp_Data[12]=(uint8_t)(((int16_t)((*(ANO_Sensors_Type*)data).GYR_Y)&0xFF00)>>8);
			Temp_Data[13]=(uint8_t)(((int16_t)((*(ANO_Sensors_Type*)data).GYR_Y)&0x00FF)>>0);
			Temp_Data[14]=(uint8_t)(((int16_t)((*(ANO_Sensors_Type*)data).GYR_Z)&0xFF00)>>8);
			Temp_Data[15]=(uint8_t)(((int16_t)((*(ANO_Sensors_Type*)data).GYR_Z)&0x00FF)>>0);
			
			Temp_Data[16]=(uint8_t)(((int16_t)((*(ANO_Sensors_Type*)data).MAG_X)&0xFF00)>>8);
			Temp_Data[17]=(uint8_t)(((int16_t)((*(ANO_Sensors_Type*)data).MAG_X)&0x00FF)>>0);
			Temp_Data[18]=(uint8_t)(((int16_t)((*(ANO_Sensors_Type*)data).MAG_Y)&0xFF00)>>8);
			Temp_Data[19]=(uint8_t)(((int16_t)((*(ANO_Sensors_Type*)data).MAG_Y)&0x00FF)>>0);
			Temp_Data[20]=(uint8_t)(((int16_t)((*(ANO_Sensors_Type*)data).MAG_Z)&0xFF00)>>8);
			Temp_Data[21]=(uint8_t)(((int16_t)((*(ANO_Sensors_Type*)data).MAG_Z)&0x00FF)>>0);
	
			Temp_Data[22]=0;
			for(i=0;i<22;i++)
			{
				Temp_Data[22]+=Temp_Data[i];
			}
		break;
		case ANO_Control:
			Temp_Data[0]=0xAA;//?????
			Temp_Data[1]=0xAA;//?????
			Temp_Data[2]=ANO_Control;//?????
			Temp_Data[3]=0x14;//?????
			Temp_Data[4]=(uint8_t)(((*(ANO_Control_Type*)data).THR&0xFF00)>>8);
			Temp_Data[5]=(uint8_t)(((*(ANO_Control_Type*)data).THR&0x00FF)>>0);
		
			Temp_Data[6]=(uint8_t)(((*(ANO_Control_Type*)data).YAW&0xFF00)>>8);
			Temp_Data[7]=(uint8_t)(((*(ANO_Control_Type*)data).YAW&0x00FF)>>0);
		
			Temp_Data[8]=(uint8_t)(((*(ANO_Control_Type*)data).ROL&0xFF00)>>8);
			Temp_Data[9]=(uint8_t)(((*(ANO_Control_Type*)data).ROL&0x00FF)>>0);
			
			Temp_Data[10]=(uint8_t)(((*(ANO_Control_Type*)data).PIT&0xFF00)>>8);
			Temp_Data[11]=(uint8_t)(((*(ANO_Control_Type*)data).PIT&0x00FF)>>0);
		
			Temp_Data[12]=(uint8_t)(((*(ANO_Control_Type*)data).AUX1&0xFF00)>>8);
			Temp_Data[13]=(uint8_t)(((*(ANO_Control_Type*)data).AUX1&0x00FF)>>0);
		
			Temp_Data[14]=(uint8_t)(((*(ANO_Control_Type*)data).AUX2&0xFF00)>>8);
			Temp_Data[15]=(uint8_t)(((*(ANO_Control_Type*)data).AUX2&0x00FF)>>0);
			
			Temp_Data[16]=(uint8_t)(((*(ANO_Control_Type*)data).AUX3&0xFF00)>>8);
			Temp_Data[17]=(uint8_t)(((*(ANO_Control_Type*)data).AUX3&0x00FF)>>0);
			
			Temp_Data[18]=(uint8_t)(((*(ANO_Control_Type*)data).AUX4&0xFF00)>>8);
			Temp_Data[19]=(uint8_t)(((*(ANO_Control_Type*)data).AUX4&0x00FF)>>0);
			
			Temp_Data[20]=(uint8_t)(((*(ANO_Control_Type*)data).AUX5&0xFF00)>>8);
			Temp_Data[21]=(uint8_t)(((*(ANO_Control_Type*)data).AUX5&0x00FF)>>0);
			
			Temp_Data[22]=(uint8_t)(((*(ANO_Control_Type*)data).AUX6&0xFF00)>>8);
			Temp_Data[23]=(uint8_t)(((*(ANO_Control_Type*)data).AUX6&0x00FF)>>0);
	
			Temp_Data[24]=0;
			for(i=0;i<24;i++)
			{
				Temp_Data[24]+=Temp_Data[i];
			}
		break;
		case ANO_PID1:
		case ANO_PID2:
		case ANO_PID3:
		case ANO_PID4:
		case ANO_PID5:
		case ANO_PID6:
			Temp_Data[0]=0xAA;//?????
			Temp_Data[1]=0xAA;//?????
			Temp_Data[2]=type;//?????
			Temp_Data[3]=0x12;//?????18
			Temp_Data[4]=(uint8_t)((((*(ANO_PID_Type*)data).PID1_P)&0xFF00)>>8);
			Temp_Data[5]=(uint8_t)((((*(ANO_PID_Type*)data).PID1_P)&0x00FF)>>0);
			Temp_Data[6]=(uint8_t)((((*(ANO_PID_Type*)data).PID1_I)&0xFF00)>>8);
			Temp_Data[7]=(uint8_t)((((*(ANO_PID_Type*)data).PID1_I)&0x00FF)>>0);
		    Temp_Data[8]=(uint8_t)((((*(ANO_PID_Type*)data).PID1_D)&0xFF00)>>8);
			Temp_Data[9]=(uint8_t)((((*(ANO_PID_Type*)data).PID1_D)&0x00FF)>>0);
			
			Temp_Data[10]=(uint8_t)((((*(ANO_PID_Type*)data).PID2_P)&0xFF00)>>8);
			Temp_Data[11]=(uint8_t)((((*(ANO_PID_Type*)data).PID2_P)&0x00FF)>>0);
			Temp_Data[12]=(uint8_t)((((*(ANO_PID_Type*)data).PID2_I)&0xFF00)>>8);
			Temp_Data[13]=(uint8_t)((((*(ANO_PID_Type*)data).PID2_I)&0x00FF)>>0);
		    Temp_Data[14]=(uint8_t)((((*(ANO_PID_Type*)data).PID2_D)&0xFF00)>>8);
			Temp_Data[15]=(uint8_t)((((*(ANO_PID_Type*)data).PID2_D)&0x00FF)>>0);
		
			Temp_Data[16]=(uint8_t)((((*(ANO_PID_Type*)data).PID3_P)&0xFF00)>>8);
			Temp_Data[17]=(uint8_t)((((*(ANO_PID_Type*)data).PID3_P)&0x00FF)>>0);
			Temp_Data[18]=(uint8_t)((((*(ANO_PID_Type*)data).PID3_I)&0xFF00)>>8);
			Temp_Data[19]=(uint8_t)((((*(ANO_PID_Type*)data).PID3_I)&0x00FF)>>0);
		    Temp_Data[20]=(uint8_t)((((*(ANO_PID_Type*)data).PID3_D)&0xFF00)>>8);
			Temp_Data[21]=(uint8_t)((((*(ANO_PID_Type*)data).PID3_D)&0x00FF)>>0);
			
			Temp_Data[22]=0;
			
			for(i=0;i<22;i++)
			{
				Temp_Data[22]+=Temp_Data[i];
			}
		break;
		case ANO_USER_1:
			Temp_Data[0]=0xAA;//??????
			Temp_Data[1]=0xAA;//??????
			Temp_Data[2]=type;//?????
			Temp_Data[3]=42;//?????
			Temp_Data[4]=(uint8_t)((*(uint32_t*)&((*(ANO_User1_Type*)data).M1_Speed)&0xFF000000)>>24);
			Temp_Data[5]=(uint8_t)((*(uint32_t*)&((*(ANO_User1_Type*)data).M1_Speed)&0x00FF0000)>>16);
			Temp_Data[6]=(uint8_t)((*(uint32_t*)&((*(ANO_User1_Type*)data).M1_Speed)&0x0000FF00)>>8);
			Temp_Data[7]=(uint8_t)((*(uint32_t*)&((*(ANO_User1_Type*)data).M1_Speed)&0x000000FF)>>0);

			Temp_Data[8]=(uint8_t)((*(uint32_t*)&((*(ANO_User1_Type*)data).M2_Speed)&0xFF000000)>>24);
			Temp_Data[9]=(uint8_t)((*(uint32_t*)&((*(ANO_User1_Type*)data).M2_Speed)&0x00FF0000)>>16);
			Temp_Data[10]=(uint8_t)((*(uint32_t*)&((*(ANO_User1_Type*)data).M2_Speed)&0x0000FF00)>>8);
			Temp_Data[11]=(uint8_t)((*(uint32_t*)&((*(ANO_User1_Type*)data).M2_Speed)&0x000000FF)>>0);
		
			Temp_Data[12]=(uint8_t)((*(uint32_t*)&((*(ANO_User1_Type*)data).M3_Speed)&0xFF000000)>>24);
			Temp_Data[13]=(uint8_t)((*(uint32_t*)&((*(ANO_User1_Type*)data).M3_Speed)&0x00FF0000)>>16);
			Temp_Data[14]=(uint8_t)((*(uint32_t*)&((*(ANO_User1_Type*)data).M3_Speed)&0x0000FF00)>>8);
			Temp_Data[15]=(uint8_t)((*(uint32_t*)&((*(ANO_User1_Type*)data).M3_Speed)&0x000000FF)>>0);
		
			Temp_Data[16]=(uint8_t)((*(uint32_t*)&((*(ANO_User1_Type*)data).M4_Speed)&0xFF000000)>>24);
			Temp_Data[17]=(uint8_t)((*(uint32_t*)&((*(ANO_User1_Type*)data).M4_Speed)&0x00FF0000)>>16);
			Temp_Data[18]=(uint8_t)((*(uint32_t*)&((*(ANO_User1_Type*)data).M4_Speed)&0x0000FF00)>>8);
			Temp_Data[19]=(uint8_t)((*(uint32_t*)&((*(ANO_User1_Type*)data).M4_Speed)&0x000000FF)>>0);

			Temp_Data[20]=(uint8_t)(((int16_t)((*(ANO_User1_Type*)data).M1_PID_OUT)&0xFF00)>>8);
			Temp_Data[21]=(uint8_t)(((int16_t)((*(ANO_User1_Type*)data).M1_PID_OUT)&0x00FF)>>0);
		
			Temp_Data[22]=(uint8_t)(((int16_t)((*(ANO_User1_Type*)data).M2_PID_OUT)&0xFF00)>>8);
			Temp_Data[23]=(uint8_t)(((int16_t)((*(ANO_User1_Type*)data).M2_PID_OUT)&0x00FF)>>0);
			
			Temp_Data[24]=(uint8_t)(((int16_t)((*(ANO_User1_Type*)data).M3_PID_OUT)&0xFF00)>>8);
			Temp_Data[25]=(uint8_t)(((int16_t)((*(ANO_User1_Type*)data).M3_PID_OUT)&0x00FF)>>0);
			
			Temp_Data[26]=(uint8_t)(((int16_t)((*(ANO_User1_Type*)data).M4_PID_OUT)&0xFF00)>>8);
			Temp_Data[27]=(uint8_t)(((int16_t)((*(ANO_User1_Type*)data).M4_PID_OUT)&0x00FF)>>0);
			
			Temp_Data[28]=(uint8_t)(((int16_t)((*(ANO_User1_Type*)data).M1_PID_Expectations)&0xFF00)>>8);
			Temp_Data[29]=(uint8_t)(((int16_t)((*(ANO_User1_Type*)data).M1_PID_Expectations)&0x00FF)>>0);
			
			Temp_Data[30]=(uint8_t)(((int16_t)((*(ANO_User1_Type*)data).M2_PID_Expectations)&0xFF00)>>8);
			Temp_Data[31]=(uint8_t)(((int16_t)((*(ANO_User1_Type*)data).M2_PID_Expectations)&0x00FF)>>0);
			
			Temp_Data[32]=(uint8_t)(((int16_t)((*(ANO_User1_Type*)data).M3_PID_Expectations)&0xFF00)>>8);
			Temp_Data[33]=(uint8_t)(((int16_t)((*(ANO_User1_Type*)data).M3_PID_Expectations)&0x00FF)>>0);
			
			Temp_Data[34]=(uint8_t)(((int16_t)((*(ANO_User1_Type*)data).M4_PID_Expectations)&0xFF00)>>8);
			Temp_Data[35]=(uint8_t)(((int16_t)((*(ANO_User1_Type*)data).M4_PID_Expectations)&0x00FF)>>0);
		
			Temp_Data[36]=(uint8_t)((((*(ANO_User1_Type*)data).Voltage_ADC)&0xFF00)>>8);
			Temp_Data[37]=(uint8_t)((((*(ANO_User1_Type*)data).Voltage_ADC)&0x00FF)>>0);
			
			Temp_Data[38]=(uint8_t)((((*(ANO_User1_Type*)data).Sever1_ADC)&0xFF00)>>8);
			Temp_Data[39]=(uint8_t)((((*(ANO_User1_Type*)data).Sever1_ADC)&0x00FF)>>0);
			
			Temp_Data[40]=(uint8_t)((((*(ANO_User1_Type*)data).Sever2_ADC)&0xFF00)>>8);
			Temp_Data[41]=(uint8_t)((((*(ANO_User1_Type*)data).Sever2_ADC)&0x00FF)>>0);
			
			Temp_Data[42]=(uint8_t)((((*(ANO_User1_Type*)data).Sever3_ADC)&0xFF00)>>8);
			Temp_Data[43]=(uint8_t)((((*(ANO_User1_Type*)data).Sever3_ADC)&0x00FF)>>0);
			
			Temp_Data[44]=(uint8_t)((((*(ANO_User1_Type*)data).Sever4_ADC)&0xFF00)>>8);
			Temp_Data[45]=(uint8_t)((((*(ANO_User1_Type*)data).Sever4_ADC)&0x00FF)>>0);
			
			Temp_Data[46]=0;
			for(i=0;i<46;i++)
			{
				Temp_Data[46]+=Temp_Data[i];
			}
		break;
	}
	for(j=0;j<=i;j++)
	{
		usart2_send_byte(Temp_Data[j]);
	}

}




/*
*@ Description ?????????????????????
*@ param ??????????
*@ param ??????????
*@ return ??????
*/
static void ANO_Return_Check(uint8_t FREAM_HEAD,uint8_t CHECK_SUM)
{
	uint8_t i,Temp_Data[7];
	Temp_Data[0]=0xAA;//??????
	Temp_Data[1]=0xAA;//??????
	Temp_Data[2]=0xEF;//??????????
	Temp_Data[3]=0x02;//??????????
	Temp_Data[4]=FREAM_HEAD;
	Temp_Data[5]=CHECK_SUM;
	Temp_Data[6]=0;
	for(i=0;i<6;i++)
	{
		Temp_Data[6]+=Temp_Data[i];
	}
	for(i=0;i<7;i++)
	{
		usart2_send_byte(Temp_Data[i]);
	}
}


/*
*@ Description ???????????????
*@ param ??????
*@ return ???????????????�?
*/
static void ANO_Upload_PID(void)
{
	ANO_PID_Type TEMP={100,200,300,400,500,600,700,800,900};
	ANO_Uploading_data(ANO_PID1,&TEMP);
	ANO_Uploading_data(ANO_PID2,&TEMP);
	ANO_Uploading_data(ANO_PID3,&TEMP);
	ANO_Uploading_data(ANO_PID4,&TEMP);
	
	Get_PID_Param(0,&TEMP.PID1_P,&TEMP.PID1_I,&TEMP.PID1_D);
	Get_PID_Param(1,&TEMP.PID2_P,&TEMP.PID2_I,&TEMP.PID2_D);
	Get_PID_Param(2,&TEMP.PID3_P,&TEMP.PID3_I,&TEMP.PID3_D);
	ANO_Uploading_data(ANO_PID5,&TEMP);
	Get_PID_Param(3,&TEMP.PID1_P,&TEMP.PID1_I,&TEMP.PID1_D);
	Get_PID_Param(4,&TEMP.PID2_P,&TEMP.PID2_I,&TEMP.PID2_D);
	
	ANO_Uploading_data(ANO_PID6,&TEMP);
}











