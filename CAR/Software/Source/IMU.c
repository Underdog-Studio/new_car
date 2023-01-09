#include "IMU.h"
static uint8_t IMU_Status;
Three_axes Gyr_Offsets={0,0,0};
uint8_t ICM20602_Init(void);
uint8_t IST8310_Init(void);
static void IMU_Offsets_Calibrate(void);
/*
*@ Description �����
*@ param �����
*@ return �����
*/
void IMU_Init(void)
{
	if(IST8310_Init())							//�����
		IMU_Status+=2;

	if(ICM20602_Init())						//����������
		IMU_Status+=1;
	
	IMU_Offsets_Calibrate();    //���������� 
}

/*
*@ Description
*@ param �����
*@ return �����
*/
uint8_t Get_IMU_Status(void)
{
	return IMU_Status;
}


/****************************************************ICM20602****************************************************/

/*
*@ Description �����
*@ param �����
*@ return �����
*/
uint8_t ICM20602_Init(void)
{
	uint8_t ID;

  I2C_Register_Write_1Byte(ICM_ADDR,0X6B,0X81);	//�����
  delay_ms(100);
  I2C_Register_Write_1Byte(ICM_ADDR,0X6B,0X01);	//�����				
	I2C_Register_Write_1Byte(ICM_ADDR,0X1B,3<<3);//�����,±2000dps
	I2C_Register_Write_1Byte(ICM_ADDR,0X1C,3<<3);					//�����,±16g
	I2C_Register_Write_1Byte(ICM_ADDR,0X19,0x00);
	I2C_Register_Write_1Byte(ICM_ADDR,0X1A,0x02);//�����
	I2C_Register_Write_1Byte(ICM_ADDR,0X38,0X00);	//�����
	I2C_Register_Write_1Byte(ICM_ADDR,0X6A,0X00);	//�����
	I2C_Register_Write_1Byte(ICM_ADDR,0X23,0X00);	//�����
	I2C_Register_Write_1Byte(ICM_ADDR,0X37,0X80);	//�����
	
	I2C_Register_Read_1Byte(ICM_ADDR,0X75,&ID);
	if(ID==0xaf)//�����  ICM20608 0xaf icm20602 18
	{
		
		I2C_Register_Write_1Byte(ICM_ADDR,0X6B,0X01);	//�����,PLL �����
		I2C_Register_Write_1Byte(ICM_ADDR,0X6C,0X00);	//�����
		I2C_Register_Write_1Byte(ICM_ADDR,0X19,0x00);
		I2C_Register_Write_1Byte(ICM_ADDR,0X1A,0x02);//�����
 	}else return 0;
	return 1;		
}

/*
*@ Description �����
*@ *Gyr �����
*@ return ����� �����
*/
uint8_t ICM_Get_Gyroscope(Three_axes *Gyr)
{
  uint8_t BUFF[6],res;  
	res=I2C_Register_Read_nByte(ICM_ADDR,0X43,BUFF,6);

	if(res==1)
	{
		Gyr->x=(int16_t)(((uint16_t)BUFF[0]<<8)|BUFF[1])/16.4f-Gyr_Offsets.x;  //16.4
		Gyr->y=(int16_t)(((uint16_t)BUFF[2]<<8)|BUFF[3])/16.4f-Gyr_Offsets.y;  
		Gyr->z=(int16_t)(((uint16_t)BUFF[4]<<8)|BUFF[5])/16.4f-Gyr_Offsets.z;
	} 	
    return res;
}

/*
*@ Description ����� 
*@ param �����
*@ return ����� �����
*/
uint8_t ICM_Get_Accelerometer(Three_axes *Acc)
{
    uint8_t buf[6],res;  
	res=I2C_Register_Read_nByte(ICM_ADDR,0X3B,buf,6);
	if(res==1)
	{
		Acc->x=(int16_t)(((uint16_t)buf[0]<<8)|buf[1])/208.98f; 
		Acc->y=(int16_t)(((uint16_t)buf[2]<<8)|buf[3])/208.98f; 
		Acc->z=(int16_t)(((uint16_t)buf[4]<<8)|buf[5])/208.98f;
	} 	
    return res;
}

/*
*@ Description �����
*@ param �����
*@ return ID
*/
uint8_t Get_ICM20602_ID(void)
{
	uint8_t ID;
	I2C_Register_Read_1Byte(ICM_ADDR,0X75,&ID);
	return ID;
}
/****************************************************ICM20602****************************************************/


/*****************************************************QMC5883****************************************************/
/*
*@ Description ����������
*@ param �����
*@ return �����
*/
uint8_t IST8310_Init(void)
{
	uint8_t ID;
	I2C_Register_Read_1Byte(IST_ADDR,0x0D,&ID);
	if(ID!=0xff)
		return 0;
	I2C_Register_Write_1Byte(IST_ADDR,0x0A,0x80);
	I2C_Register_Write_1Byte(IST_ADDR,0x09,0x1D);
	I2C_Register_Write_1Byte(IST_ADDR,0x20,0x40);
	I2C_Register_Write_1Byte(IST_ADDR,0x21,0x01);
	I2C_Register_Write_1Byte(IST_ADDR,0x0B,0x01);
	I2C_Register_Write_1Byte(IST_ADDR,0x0A,0x01);
	return 1;
}

/*
*@ Description �����
*@ param �����
*@ return ����� �����
*/
uint8_t IST_Get_Geomagnetism(Three_axes *Mag)
{
  uint8_t buf[6],res; 
	res=I2C_Register_Read_nByte(IST_ADDR,0x00,buf,6);
	if(res==1)
	{
		Mag->x=(int16_t)(((uint16_t)buf[1]<<8)|buf[0])/3.0f;  //16.4
		Mag->y=(int16_t)(((uint16_t)buf[3]<<8)|buf[2])/3.0f;  
		Mag->z=(int16_t)(((uint16_t)buf[5]<<8)|buf[4])/3.0f;
	} 	
    return res;
}
/*****************************************************IST8310****************************************************/


/*
*@ Description �����
*@ param �����
*@ return �����
*/
static void IMU_Offsets_Calibrate(void)
{
	uint16_t i,Calibrate_Count=0;
	uint8_t Calibrate_Start=0;
	Three_axes Gyr,Last_Gyr,temp;
	ICM_Get_Gyroscope(&Last_Gyr);
	
	while(1)
	{
		ICM_Get_Gyroscope(&Gyr);
		switch(Calibrate_Start)
		{
			case 0:
				ws2812_Control(255,0,0);
				if((My_absf(Gyr.x-Last_Gyr.x) <= 0.5f) && (My_absf(Gyr.y-Last_Gyr.y) <= 0.5f) && (My_absf(Gyr.z-Last_Gyr.z) <= 0.5f))//�����
				{
					if(Calibrate_Count++ >=100)//�����.�����
					{
						Calibrate_Start=1;//�����
						Calibrate_Count=0;
					}
				}else
				{
					Calibrate_Count=0;
				}
			break;
			case 1://�����
				if((My_absf(Gyr.x-Last_Gyr.x) <= 0.5f) && (My_absf(Gyr.y-Last_Gyr.y) <= 0.5f) && (My_absf(Gyr.z-Last_Gyr.z) <= 0.5f))//�����
				{
					ws2812_Control(Calibrate_Count,0,Calibrate_Count);
					if(Calibrate_Count++ <500)//�����
					{
							temp.x += Gyr.x;
							temp.y += Gyr.y;
							temp.z += Gyr.z;
					}else
					{
							//�����
							temp.x/=500.0f;
							temp.y/=500.0f;
							temp.z/=500.0f; 
							Gyr_Offsets = temp;
							Calibrate_Start=2;
					}
				}else
				{
					temp.x=0;
					temp.y=0;
					temp.z=0;
					Calibrate_Start=0;//�����
					Calibrate_Count=0;
				}
			break;
		}
		Last_Gyr.x = Gyr.x;
		Last_Gyr.y = Gyr.y;
		Last_Gyr.z = Gyr.z;
		if(Calibrate_Start==2)
			break;
		delay_ms(5);
	}
  Set_Buzzer(384,3);
	vTaskDelay(200);
	Set_Buzzer(426,3);
	vTaskDelay(200);
	Set_Buzzer(480,3);
	vTaskDelay(200);
	Set_Buzzer(512,3);
	vTaskDelay(200);
	Buzzer_Disable();
}
/**
*@Description :�����
*@return      :�����
**/
Three_axes Get_Gyr_Offsets(void)
{
	return Gyr_Offsets;
}



