#include "PID.h"


/*
*@ Description :�����
*@ param PID
*/
void PID_Incremental_Calculate(PID_Type *Parameter)
{
	//�����
	Parameter->Error=Parameter->Target - Parameter->Observed;//����� - �����
	
	//�����
	Parameter->P_Value=Parameter->P*(Parameter->Error-Parameter->Last_Error);
	
	//�����
	Parameter->I_Value=Parameter->I*Parameter->Error;
	
	//�����
	Parameter->D_Value=Parameter->D*(Parameter->Error-2*Parameter->Last_Error+Parameter->Previous_Error);
	//�����
	Parameter->Previous_Error=Parameter->Last_Error;
	Parameter->Last_Error=Parameter->Error;
	
	//�����
	Parameter->PID_Out+=Parameter->P_Value+Parameter->I_Value+Parameter->D_Value;
	
	//�����
	if(Parameter->PID_Out<Parameter->PID_Min)
		Parameter->PID_Out=Parameter->PID_Min;
	if(Parameter->PID_Out>Parameter->PID_Max)
		Parameter->PID_Out=Parameter->PID_Max;
}


/*
*@ Description :�����
*@ param PID
*/
void PID_Positional_Calculate(PID_Type *Parameter)
{
	//�����
	Parameter->Error=Parameter->Target - Parameter->Observed;//����� - �����
	//�����
	Parameter->P_Value = Parameter->P * Parameter->Error;
	//�����
	Parameter->I_Value += Parameter->I * Parameter->Error;
	//�����
	if(Parameter->I_Value<Parameter->I_Min)
		Parameter->I_Value=Parameter->I_Min;
	if(Parameter->I_Value>Parameter->I_Max)
		Parameter->I_Value=Parameter->I_Max;
	//�����
	Parameter->D_Value = Parameter->D * (Parameter->Last_Error-Parameter->Error);
	Parameter->Last_Error = Parameter->Error;
	Parameter->PID_Out = Parameter->P_Value + Parameter->I_Value + Parameter->D_Value;
	//�����
	if(Parameter->PID_Out<Parameter->PID_Min)
		Parameter->PID_Out=Parameter->PID_Min;
	if(Parameter->PID_Out>Parameter->PID_Max)
		Parameter->PID_Out=Parameter->PID_Max;
}




