#ifndef __Filter_H
#define __Filter_H



typedef struct
{
 float Input_Butter[3];
 float Output_Butter[3];
}Butter_BufferData;//������������˲��������ݽṹ���������


typedef struct
{
  float a[3];
  float b[3];
}Butter_Parameter;//���������Ȳ�������ṹ���������





//�������������˲����
float LPButterworth(float curr_input,Butter_BufferData *Buffer,Butter_Parameter *Parameter);
#endif
