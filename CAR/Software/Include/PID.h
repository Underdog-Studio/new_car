#ifndef __PID_H
#define __PID_H

//PID����������������
typedef struct
{
	float Target;//�������ֵ�
	float Observed;//��۲�ֵ�
	float Error;//������
	float Last_Error;//��ϴ�������
	float Previous_Error;//������ϴ���������
	float PID_Max;//�������޷�������ֵ�
	float PID_Min;//��������޷�����Сֵ�
	float I_Max;//���������޷�����ֵ
	float I_Min;//����������޷������Сֵ
	float P;//��������������
	float I;//�����ֲ������
	float D;//΢�ֲ������
	float P_Value;//��������
	float I_Value;//��������
	float D_Value;//΢��
	float PID_Out;//PID������
}PID_Type;




//PID�������
void PID_Incremental_Calculate(PID_Type *Parameter);
void PID_Positional_Calculate(PID_Type *Parameter);








#endif
