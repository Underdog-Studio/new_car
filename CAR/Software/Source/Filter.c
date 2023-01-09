#include "Filter.h"

Butter_Parameter Butter_30HZ_Parameter_Acce={
//333hz---20hz
           1.0f, -1.474969547862f, 0.586607194895f,
0.027909411758f,  0.055818823516f, 0.027909411758f  

};

Butter_Parameter Butter_15HZ_Parameter_Acce={
//200hz---1hz
1.0f	        ,-1.973317570464,0.973668890311 , 
0.000087829962,0.000175659924   ,0.000087829962
};



/*
*@ Description ����� 
*@ param ����� 
*@ param �����
*@ param �����
*@ return �����
*/
float LPButterworth(float curr_input,Butter_BufferData *Buffer,Butter_Parameter *Parameter)
{
  /* �����(n) */
  static int LPF_Cnt=0;
  Buffer->Input_Butter[2]=curr_input;
  if(LPF_Cnt>=100)
  {
    /* ����� */
    Buffer->Output_Butter[2]=
      Parameter->b[0] * Buffer->Input_Butter[2]
        +Parameter->b[1] * Buffer->Input_Butter[1]
          +Parameter->b[2] * Buffer->Input_Butter[0]
            -Parameter->a[1] * Buffer->Output_Butter[1]
              -Parameter->a[2] * Buffer->Output_Butter[0];
  }
  else
  {
    Buffer->Output_Butter[2]=Buffer->Input_Butter[2];
    LPF_Cnt++;
  }
  /* x(n) ����� */
  Buffer->Input_Butter[0]=Buffer->Input_Butter[1];
  Buffer->Input_Butter[1]=Buffer->Input_Butter[2];
  /* y(n) ����� */
  Buffer->Output_Butter[0]=Buffer->Output_Butter[1];
  Buffer->Output_Butter[1]=Buffer->Output_Butter[2];
  return Buffer->Output_Butter[2];
}

