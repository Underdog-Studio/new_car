#include "UDPI_Connect.h"

//?????????

#define UDPI_STK_SIZE			128
TaskHandle_t UDPI_Task_Handler;
void UDPI_Mainfunc(void *pvParameters);

ringBuffer_t UDPI_Data_Buffer;



static void UDPI_Return_Check(uint8_t FREAM_HEAD,uint8_t CHECK_SUM);
static void UDPI_Uploading_data(uint8_t type,void *data);
QueueHandle_t xQueue_UDPI_RX;//?????????

static void UDPI_USART_Callback_Register(uint8_t data); //?????????

/**
*@Description :???????????????
**/
void UDPI_Connect_Init(void)
{
	usart1_init(115200);
	USART1_IRQ_Callback_Register(UDPI_USART_Callback_Register);
	
//	xQueue_UDPI_RX = xQueueCreate(1000,sizeof(uint8_t));//?????????
	RingBuffer_Init(&UDPI_Data_Buffer);
	xTaskCreate((TaskFunction_t		)UDPI_Mainfunc,
					(const char*			)"UDPI_Mainfunc",
					(uint16_t					)UDPI_STK_SIZE,
					(void*						)NULL,
					(UBaseType_t			)UDPI_TASK_PRIO,
					(TaskHandle_t*		)&UDPI_Task_Handler);//?????????
}




/**
*@Description :?????????
*@param       :?????????
**/
static void UDPI_USART_Callback_Register(uint8_t data)
{
	//xQueueSendFromISR(xQueue_UDPI_RX,&data,0);//????????????
	RingBuffer_Write(&UDPI_Data_Buffer,&data);
}

//?????????
uint8_t UDPI_Receive_State=0,//??????
						 UDPI_Function=0xff,  //?????? ??????
             UDPI_Data_Len=0,     //?????? ??????
             UDPI_Data_Receive_Len=0, //?????? ??????
             UDPI_Receive_Data[50];   //?????????
uint16_t UDPI_SUM=0; //??????
void UDPI_Mainfunc(void *pvParameters)
{
	void *upload_data;
	uint8_t temp;
	while(1)
	{
		//while(xQueueReceive(xQueue_UDPI_RX,&temp,0)==pdTRUE)
		while(RingBuffer_Read(&UDPI_Data_Buffer,&temp))
		{
			switch(UDPI_Receive_State)
			{
				case 0:
				{
					if(temp==0xAB)//?????????
					{
						UDPI_SUM=0;
						UDPI_Receive_State++;
						UDPI_SUM+=temp;
					}
				break;
				}
				case 1:
				{
					if(UDPI_Function==0xff)//?????????
					{
						UDPI_Function=temp;//??????
						UDPI_Receive_State++;
						UDPI_SUM+=temp;
					}else                 //???
					{
						UDPI_Receive_State=0;//???????????????
						UDPI_Function=0xff;//?????????
					}
				break;
				}
				case 2:
				{
						if(UDPI_Data_Len==0)//?????????
						{
							UDPI_Data_Len=temp;//?????????
							UDPI_Data_Receive_Len = 0;
							UDPI_Receive_State++;
							UDPI_SUM+=temp;
						}else                 //????????????
						{
							UDPI_Receive_State=0;
							UDPI_Function=0xff;//????????????
							UDPI_Data_Len=0;//????????????
						}
					break;
				}
				case 3:
				{
						UDPI_Receive_Data[UDPI_Data_Receive_Len++]=temp;//????????????
						if(UDPI_Data_Receive_Len == (UDPI_Data_Len+1))
						{
							if(UDPI_Receive_Data[UDPI_Data_Len] == (UDPI_SUM%256))
							{
								switch(UDPI_Function)//?????? ????????????
								{
									case UDPI_X_Axis://?????????
										Set_Move(0,(int16_t)(((int16_t)UDPI_Receive_Data[0]<<8)|UDPI_Receive_Data[1]),(int16_t)(((int16_t)UDPI_Receive_Data[2]<<8)|UDPI_Receive_Data[3]),(int16_t)(((int16_t)UDPI_Receive_Data[4]<<8)|UDPI_Receive_Data[5]));
										UDPI_Return_Check(UDPI_Function,UDPI_SUM%256);
									break;
									case UDPI_Y_Axis://??????
										Set_Move(1,(int16_t)(((int16_t)UDPI_Receive_Data[0]<<8)|UDPI_Receive_Data[1]),(int16_t)(((int16_t)UDPI_Receive_Data[2]<<8)|UDPI_Receive_Data[3]),(int16_t)(((int16_t)UDPI_Receive_Data[4]<<8)|UDPI_Receive_Data[5]));
										UDPI_Return_Check(UDPI_Function,UDPI_SUM%256);
									break;
									case UDPI_Yaw_Axis://??????
										Set_Move(2,(int16_t)(((int16_t)UDPI_Receive_Data[0]<<8)|UDPI_Receive_Data[1]),(int16_t)(((int16_t)UDPI_Receive_Data[2]<<8)|UDPI_Receive_Data[3]),(int16_t)(((int16_t)UDPI_Receive_Data[4]<<8)|UDPI_Receive_Data[5]));
										UDPI_Return_Check(UDPI_Function,UDPI_SUM%256);
									break;
									case UDPI_Servo://??????
										switch(UDPI_Receive_Data[0])
										{
											case 0x01://??????
												Servo_Pos_Control(1,(float)(((int16_t)UDPI_Receive_Data[1]<<8)|UDPI_Receive_Data[2]));
											break;
											case 0x02://??????
												Servo_Pos_Control(2,(float)(((int16_t)UDPI_Receive_Data[1]<<8)|UDPI_Receive_Data[2]));
											break;
											case 0x03://??????
												Servo_Pos_Control(3,(float)(((int16_t)UDPI_Receive_Data[1]<<8)|UDPI_Receive_Data[2]));
											break;
											case 0x04://??????
												Servo_Pos_Control(4,(float)(((int16_t)UDPI_Receive_Data[1]<<8)|UDPI_Receive_Data[2]));
											break;
										}
										UDPI_Return_Check(UDPI_Function,UDPI_SUM%256);
									break;

									case Get_Move://??????
									{
										switch (UDPI_Receive_Data[0])
										{
										case 0x01://?????????
											upload_data = (UDPI_Move_data*)pvPortMalloc(sizeof(UDPI_Move_data));

											(*(UDPI_Move_data*)upload_data).Distance = 0;
											(*(UDPI_Move_data*)upload_data).Velocity = (int16_t)(Get_X_Body_Vel()*100.0f);
											(*(UDPI_Move_data*)upload_data).Acceleration = (int16_t)(Get_Primeval_Acc().x*100.0f);
											UDPI_Uploading_data(UDPI_X_Axis,upload_data);
											vPortFree(upload_data);
											break;
										case 0x02://?????????
											upload_data = (UDPI_Move_data*)pvPortMalloc(sizeof(UDPI_Move_data));

											(*(UDPI_Move_data*)upload_data).Distance = 0;
											(*(UDPI_Move_data*)upload_data).Velocity = (int16_t)(Get_Y_Body_Vel()*100.0f);
											(*(UDPI_Move_data*)upload_data).Acceleration = (int16_t)(Get_Primeval_Acc().y*100.0f);
											UDPI_Uploading_data(UDPI_Y_Axis,upload_data);
											vPortFree(upload_data);	
											break;
										case 0x03://?????????
											upload_data = (UDPI_Move_data*)pvPortMalloc(sizeof(UDPI_Move_data));

											(*(UDPI_Move_data*)upload_data).Distance = 0;
											(*(UDPI_Move_data*)upload_data).Velocity = (int16_t)(Get_Yaw_Body_Vel()*100.0f);
											(*(UDPI_Move_data*)upload_data).Acceleration = 0;
											UDPI_Uploading_data(UDPI_Yaw_Axis,upload_data);
											vPortFree(upload_data);
											break;
										default:
											break;
										}
									break;
									}
									case Get_Servo://?????????
									switch (UDPI_Receive_Data[0])
									{
										case 0x01://??????
											upload_data = (UDPI_Move_data*)pvPortMalloc(sizeof(UDPI_Move_data));

												(*(UDPI_Move_data*)upload_data).Distance = 0;
												(*(UDPI_Move_data*)upload_data).Velocity = 0;
												(*(UDPI_Move_data*)upload_data).Acceleration = 0;
												UDPI_Uploading_data(UDPI_Yaw_Axis,upload_data);
												vPortFree(upload_data);
											break;
										case 0x02://??????
											upload_data = (UDPI_Move_data*)pvPortMalloc(sizeof(UDPI_Move_data));

												(*(UDPI_Move_data*)upload_data).Distance = 0;
												(*(UDPI_Move_data*)upload_data).Velocity = 0;
												(*(UDPI_Move_data*)upload_data).Acceleration = 0;
												UDPI_Uploading_data(UDPI_Yaw_Axis,upload_data);
												vPortFree(upload_data);
											break;
										case 0x03://??????
											upload_data = (UDPI_Move_data*)pvPortMalloc(sizeof(UDPI_Move_data));

												(*(UDPI_Move_data*)upload_data).Distance = 0;
												(*(UDPI_Move_data*)upload_data).Velocity = 0;
												(*(UDPI_Move_data*)upload_data).Acceleration = 0;
												UDPI_Uploading_data(UDPI_Yaw_Axis,upload_data);
												vPortFree(upload_data);
											break;
										case 0x04://??????
											upload_data = (UDPI_Move_data*)pvPortMalloc(sizeof(UDPI_Move_data));

												(*(UDPI_Move_data*)upload_data).Distance = 0;
												(*(UDPI_Move_data*)upload_data).Velocity = 0;
												(*(UDPI_Move_data*)upload_data).Acceleration = 0;
												UDPI_Uploading_data(UDPI_Yaw_Axis,upload_data);
												vPortFree(upload_data);
											break;
										default:
											break;
									}	
									break;
									case Get_State://????????????
										upload_data = (UDPI_state_data*)pvPortMalloc(sizeof(UDPI_state_data));

										(*(UDPI_state_data*)upload_data).X_Axis = Get_X_State();
										(*(UDPI_state_data*)upload_data).Y_Axis = Get_Y_State();
										(*(UDPI_state_data*)upload_data).Yaw_Axis = Get_Yaw_State();
										UDPI_Uploading_data(Get_State,upload_data);
										vPortFree(upload_data);
									break;
								}
							}
							UDPI_Receive_State=0;
							UDPI_Function=0xff;//????????????
							UDPI_Data_Len=0;//????????????
						}
					UDPI_SUM+=temp;
					break;
				}
			}
		}
		vTaskDelay(10);
	}
}


/**
*@Description :???????????????
*@param       :??????
*@param       :??????
**/
static void UDPI_Return_Check(uint8_t FREAM_HEAD,uint8_t CHECK_SUM)
{
	uint8_t i,Temp_Data[7];
	Temp_Data[0]=0xAA;//???
	Temp_Data[1]=0xAA;//???
	Temp_Data[2]=0xEF;//??????
	Temp_Data[3]=0x02;//??????
	Temp_Data[4]=FREAM_HEAD;
	Temp_Data[5]=CHECK_SUM;
	Temp_Data[6]=0;
	for(i=0;i<6;i++)
	{
		Temp_Data[6]+=Temp_Data[i];
	}
	for(i=0;i<7;i++)
	{
		usart1_send_byte(Temp_Data[i]);
	}
}




static void UDPI_Uploading_data(uint8_t type,void *data)
{
	uint8_t Temp_Data[30],i,j;
	switch(type)
	{
		case UDPI_X_Axis://????????????
			Temp_Data[ 0] = 0xBA;//??????
			Temp_Data[ 1] = UDPI_X_Axis;//?????????
			Temp_Data[ 2] = 6;//???

			Temp_Data[ 3] = (*(UDPI_Move_data*)data).Distance>>0;
			Temp_Data[ 4] = (*(UDPI_Move_data*)data).Distance>>8;
			Temp_Data[ 5] = (*(UDPI_Move_data*)data).Velocity>>0;
			Temp_Data[ 6] = (*(UDPI_Move_data*)data).Velocity>>8;
			Temp_Data[ 7] = (*(UDPI_Move_data*)data).Acceleration>>0;
			Temp_Data[ 8] = (*(UDPI_Move_data*)data).Acceleration>>8;
			Temp_Data[ 9] = 0;
			for(i=0;i<9;i++)
			{
				Temp_Data[9]+=Temp_Data[i];
			}
		break;
		case UDPI_Y_Axis://????????????
			Temp_Data[ 0] = 0xBA;//???
			Temp_Data[ 1] = UDPI_Y_Axis;//??????
			Temp_Data[ 2] = 6;//?????????

			Temp_Data[ 3] = (*(UDPI_Move_data*)data).Distance>>0;
			Temp_Data[ 4] = (*(UDPI_Move_data*)data).Distance>>8;
			Temp_Data[ 5] = (*(UDPI_Move_data*)data).Velocity>>0;
			Temp_Data[ 6] = (*(UDPI_Move_data*)data).Velocity>>8;
			Temp_Data[ 7] = (*(UDPI_Move_data*)data).Acceleration>>0;
			Temp_Data[ 8] = (*(UDPI_Move_data*)data).Acceleration>>8;
			Temp_Data[ 9] = 0;
			for(i=0;i<9;i++)
			{
				Temp_Data[9]+=Temp_Data[i];
			}
		break;
		case UDPI_Yaw_Axis://??????
			Temp_Data[ 0] = 0xBA;//???
			Temp_Data[ 1] = UDPI_Yaw_Axis;//???
			Temp_Data[ 2] = 6;//???

			Temp_Data[ 3] = (*(UDPI_Move_data*)data).Distance>>0;
			Temp_Data[ 4] = (*(UDPI_Move_data*)data).Distance>>8;
			Temp_Data[ 5] = (*(UDPI_Move_data*)data).Velocity>>0;
			Temp_Data[ 6] = (*(UDPI_Move_data*)data).Velocity>>8;
			Temp_Data[ 7] = (*(UDPI_Move_data*)data).Acceleration>>0;
			Temp_Data[ 8] = (*(UDPI_Move_data*)data).Acceleration>>8;
			Temp_Data[ 9] = 0;
			for(i=0;i<9;i++)
			{
				Temp_Data[9]+=Temp_Data[i];
			}
		break;
		case Get_State://??????
			Temp_Data[ 0] = 0xBA;//???
			Temp_Data[ 1] = Get_State;//???
			Temp_Data[ 2] = 3;//???
			
			Temp_Data[ 3] = (*(UDPI_state_data*)data).X_Axis;
			Temp_Data[ 4] = (*(UDPI_state_data*)data).Y_Axis;
			Temp_Data[ 5] = (*(UDPI_state_data*)data).Yaw_Axis;

			Temp_Data[ 6] = 0;
			for(i=0;i<6;i++)
			{
				Temp_Data[6]+=Temp_Data[i];
			}
		break;
	}
	for(j=0;j<=i;j++)
	{
		usart1_send_byte(Temp_Data[j]);
	}
}







