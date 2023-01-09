#include "Ymodem.h"

uint32_t FlashDestination = ApplicationAddress;
uint8_t file_name[256],file_size[16];//接收文件名字与文件大小

static int8_t Receive_packet(uint8_t *data, int *length, float timeout);
static int Str_to_int(uint8_t *String);
void Ymodem_Recive_Callback(uint8_t data);
int8_t Receive_byte(uint8_t *data,float timeout);
static uint32_t FLASH_PagesMask(__IO uint32_t Size);

/*
*@ Description:Ymodem文件传输初始化
*/
void Ymodem_init(void)
{
	USART2_IRQ_Callback_Register(Ymodem_Recive_Callback);
}


/*
*@ Description:Ymodem文件传输协议 接收
*@ return - 是否成功接收
*/
char Ymodem_Receive(void)
{
	uint32_t Erases_num = 0;
	uint8_t packet_data[PACKET_1K_SIZE + PACKET_TRAILER],TEMP_Buf[1024];
	int i,j,Packet_length,EOT_Count=0,Packet_Count=0,size=0;
	while(1)
	{
		switch(Receive_packet(packet_data,&Packet_length,0.5f))
		{
			/********接收无误可以继续接收********/
			case CATCH:
				if(EOT_Count==2)//EOT已经收到两次
				{
					usart2_send_byte(ACK);
					return 1;//接收完毕
				}
				if(Packet_Count==0)//第一个包
				{
					for(i=0;packet_data[i]!=0;i++)//文件名
					{
						file_name[i]=packet_data[i];
					}
					file_name[i++]='\0';
					for(j=0;packet_data[i]!=0;i++,j++)//文件大小
					{
						file_size[j]=packet_data[i];
					}
					file_size[i++]='\0';
					size=Str_to_int(file_size);
					if(size>(FLASH_SIZE-1))//判断falsh是否够大
					{
//						 Send_Byte(CA);
//             Send_Byte(CA);
						 return 0;
					}
					//Erases_num=FLASH_PagesMask(size);//计算需要擦除多少个扇区
					Flash_Erase(ApplicationAddress,size);
					usart2_send_byte(ACK);
					usart2_send_byte('C');
				}else//第二个包开始
				{
					memcpy(TEMP_Buf,packet_data,Packet_length);//拷贝数据
					
					Flash_Write(FlashDestination,TEMP_Buf,Packet_length);//写入flash

					FlashDestination+=Packet_length;
					usart2_send_byte(ACK);
				}
				Packet_Count++;//数据包计数
				break;
			/********本次包接收出错重新接收********/
			case REPASS:
				usart2_send_byte(NAK);
				break;
			/***********所有数据接收完成***********/
			case FINISH:
				EOT_Count++;
				if(EOT_Count==1)//第一次EOT
					usart2_send_byte(NAK);
				if(EOT_Count==2)//第二次EOT
				{
					usart2_send_byte(ACK);
					usart2_send_byte('C');
				}
				break;
			/***************接收失败************/
			case FIAILED:
				return 0;
				break;
			
		}
	}
}


/*
*@ Description:Ymodem接收一个包
*@ return - 是否成功接收
*@ param 1 数据包存放指针
*@ param 2 数据包数量
*@ param 3 接收溢出时间
*/
static int8_t Receive_packet(uint8_t *data, int *length, float timeout)
{
	int16_t i,Packet_size;
	uint8_t Temp_data,Serial_number1,Serial_number2;
	if(Receive_byte(&Temp_data,timeout)==0)//未接收到数据
	{
		return FIAILED;//接收失败
	}
	switch(Temp_data)
	{
		case SOH:
			Packet_size = PACKET_128b_SIZE; //128字节的数据包
			break;
		case STX:
			Packet_size = PACKET_1K_SIZE; //1k字节的包
			break;
		case EOT:
			return FINISH;                     //接收结束
			break;
	}
	Receive_byte(&Serial_number1,timeout);//数据包编号
	Receive_byte(&Serial_number2,timeout);//数据包编号反码
	if(Serial_number1!=((Serial_number2 ^ 0xff) & 0xff))//编号对应编号的反码是否正确
	{
		return REPASS;                          //重传
	}
	//正常接收 进入接收数据阶段
	for(i=0;i<(Packet_size+PACKET_TRAILER);i++) //接收1024(数据)+2(CRC)=1026(字节)
	{
		while(Receive_byte(data+i,timeout)!=1);//数据接收失败

	}

	*length = Packet_size;
	return CATCH;//继续接收
}

int My_Pow(int num, uint8_t n)
{
	int num_temp=1;
	for(;n!=0;n--)
		num_temp*=num;
	return num_temp;
}

/*
*@ Description:字符串转整数
*@ return 转换后的整数
*@ param 1 字符串指针
*/
static int Str_to_int(uint8_t *String)
{
	uint32_t Int_num=0;
	uint8_t i,j;
	for(i=0;i<16;i++)
	{
		if(String[i]=='\0')
		{
			break;
		}
	}
	for(j=0;j<i;j++)
	{
		
		if(String[i-j-1]>='0'&&String[i-j-1]<='9')
		{
			
			Int_num+=(String[i-j-1]-'0')*My_Pow(10,j);
		}
		if(String[i-j-1]>='a'&&String[i-j-1]<='f')
		{
		
			Int_num+=((String[i-j-1]-'a')+0x0a)*My_Pow(10,j);
		}
		if(String[i-j-1]>='A'&&String[i-j-1]<='F')
		{
			
			Int_num+=((String[i-j-1]-'A')+0x0a)*My_Pow(10,j);
		}
	}
	
	return Int_num;
}

/*
*@ Description:获取要擦除的falsh扇区数量
*@ return 扇区数量
*@ param 1 文件大小
*/
static uint32_t FLASH_PagesMask(__IO uint32_t Size)
{
  uint32_t pagenumber = 0x0;
  uint32_t size = Size;

  if ((size % PAGE_SIZE) != 0)
  {
    pagenumber = (size / PAGE_SIZE) + 2;
  }
  else
  {
    pagenumber = size / PAGE_SIZE;
  }
  return pagenumber;

}


ringBuffer_t Uart_buff;//串口接受缓冲区
uint8_t Connecting;
/*
*@ Description:读取缓冲区1字节
*@ return - 是否成功接收
*@ param 1 接收到数据后所要存储的位置的指针
*@ param 2 接收数据溢出时间
*/
Time Receive_T;
int8_t Receive_byte(uint8_t *data,float timeout)
{
	uint16_t i=0;
	Receive_T=Get_System_T();
	while(Get_deta_T(Receive_T) < timeout)
  {
    if (RingBuffer_Read(&Uart_buff,data,1))
    {
      return 1;
    }
  }
  return 0;
}

/*
*@ Description:串口接收回调函数
*/
void Ymodem_Recive_Callback(uint8_t data)
{
	uint8_t temp= data;
	if(Connecting==0&&temp==0x01)
	{
		Connecting=1;
	}
	RingBuffer_Write(&Uart_buff,&temp,1);
}

/*
*@ Description:获取连接状态
*@ return 是否已连接
*/
uint8_t Get_Connecting(void)
{
	return Connecting;
}