#include "Ymodem.h"

uint32_t FlashDestination = ApplicationAddress;
uint8_t file_name[256],file_size[16];//�����ļ��������ļ���С

static int8_t Receive_packet(uint8_t *data, int *length, float timeout);
static int Str_to_int(uint8_t *String);
void Ymodem_Recive_Callback(uint8_t data);
int8_t Receive_byte(uint8_t *data,float timeout);
static uint32_t FLASH_PagesMask(__IO uint32_t Size);

/*
*@ Description:Ymodem�ļ������ʼ��
*/
void Ymodem_init(void)
{
	USART2_IRQ_Callback_Register(Ymodem_Recive_Callback);
}


/*
*@ Description:Ymodem�ļ�����Э�� ����
*@ return - �Ƿ�ɹ�����
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
			/********����������Լ�������********/
			case CATCH:
				if(EOT_Count==2)//EOT�Ѿ��յ�����
				{
					usart2_send_byte(ACK);
					return 1;//�������
				}
				if(Packet_Count==0)//��һ����
				{
					for(i=0;packet_data[i]!=0;i++)//�ļ���
					{
						file_name[i]=packet_data[i];
					}
					file_name[i++]='\0';
					for(j=0;packet_data[i]!=0;i++,j++)//�ļ���С
					{
						file_size[j]=packet_data[i];
					}
					file_size[i++]='\0';
					size=Str_to_int(file_size);
					if(size>(FLASH_SIZE-1))//�ж�falsh�Ƿ񹻴�
					{
//						 Send_Byte(CA);
//             Send_Byte(CA);
						 return 0;
					}
					//Erases_num=FLASH_PagesMask(size);//������Ҫ�������ٸ�����
					Flash_Erase(ApplicationAddress,size);
					usart2_send_byte(ACK);
					usart2_send_byte('C');
				}else//�ڶ�������ʼ
				{
					memcpy(TEMP_Buf,packet_data,Packet_length);//��������
					
					Flash_Write(FlashDestination,TEMP_Buf,Packet_length);//д��flash

					FlashDestination+=Packet_length;
					usart2_send_byte(ACK);
				}
				Packet_Count++;//���ݰ�����
				break;
			/********���ΰ����ճ������½���********/
			case REPASS:
				usart2_send_byte(NAK);
				break;
			/***********�������ݽ������***********/
			case FINISH:
				EOT_Count++;
				if(EOT_Count==1)//��һ��EOT
					usart2_send_byte(NAK);
				if(EOT_Count==2)//�ڶ���EOT
				{
					usart2_send_byte(ACK);
					usart2_send_byte('C');
				}
				break;
			/***************����ʧ��************/
			case FIAILED:
				return 0;
				break;
			
		}
	}
}


/*
*@ Description:Ymodem����һ����
*@ return - �Ƿ�ɹ�����
*@ param 1 ���ݰ����ָ��
*@ param 2 ���ݰ�����
*@ param 3 �������ʱ��
*/
static int8_t Receive_packet(uint8_t *data, int *length, float timeout)
{
	int16_t i,Packet_size;
	uint8_t Temp_data,Serial_number1,Serial_number2;
	if(Receive_byte(&Temp_data,timeout)==0)//δ���յ�����
	{
		return FIAILED;//����ʧ��
	}
	switch(Temp_data)
	{
		case SOH:
			Packet_size = PACKET_128b_SIZE; //128�ֽڵ����ݰ�
			break;
		case STX:
			Packet_size = PACKET_1K_SIZE; //1k�ֽڵİ�
			break;
		case EOT:
			return FINISH;                     //���ս���
			break;
	}
	Receive_byte(&Serial_number1,timeout);//���ݰ����
	Receive_byte(&Serial_number2,timeout);//���ݰ���ŷ���
	if(Serial_number1!=((Serial_number2 ^ 0xff) & 0xff))//��Ŷ�Ӧ��ŵķ����Ƿ���ȷ
	{
		return REPASS;                          //�ش�
	}
	//�������� ����������ݽ׶�
	for(i=0;i<(Packet_size+PACKET_TRAILER);i++) //����1024(����)+2(CRC)=1026(�ֽ�)
	{
		while(Receive_byte(data+i,timeout)!=1);//���ݽ���ʧ��

	}

	*length = Packet_size;
	return CATCH;//��������
}

int My_Pow(int num, uint8_t n)
{
	int num_temp=1;
	for(;n!=0;n--)
		num_temp*=num;
	return num_temp;
}

/*
*@ Description:�ַ���ת����
*@ return ת���������
*@ param 1 �ַ���ָ��
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
*@ Description:��ȡҪ������falsh��������
*@ return ��������
*@ param 1 �ļ���С
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


ringBuffer_t Uart_buff;//���ڽ��ܻ�����
uint8_t Connecting;
/*
*@ Description:��ȡ������1�ֽ�
*@ return - �Ƿ�ɹ�����
*@ param 1 ���յ����ݺ���Ҫ�洢��λ�õ�ָ��
*@ param 2 �����������ʱ��
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
*@ Description:���ڽ��ջص�����
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
*@ Description:��ȡ����״̬
*@ return �Ƿ�������
*/
uint8_t Get_Connecting(void)
{
	return Connecting;
}