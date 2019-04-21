#include "stepdistance.h"
int CalStepNumber(float alldistance,float distancehope,int required_remainder,float *step_distance)
{
	float deviation = 70;
	int steps_far =0,steps_near = 0,steps_medium = 0,steps_result;
	steps_far = 2*MyFloor(alldistance - distancehope*(float)required_remainder)/(2.0f*(distancehope+deviation));
	steps_medium = 2*MyClose(alldistance - distancehope*(float)required_remainder)/(2.0f*distancehope);
	steps_near =  2*MyCeil(alldistance - distancehope*(float)required_remainder)/(2.0f*(distancehope-deviation));
	steps_result = MyClose(CompareMin((float)steps_medium,(float)steps_near));
	steps_result = MyClose(CompareMax((float)steps_far,(float)steps_result));
	(*step_distance) = (alldistance - distancehope*(float)required_remainder)/steps_result;
	return (steps_result+required_remainder);
}

float CalStepDistance(float targetposition,float currentposition,float distancehope,LegState targetleg)
{
	float result = 0;
	int required_step_number = 0;
	//int required_remainder = 0;
	float distance_all = 0;
	distance_all = targetposition - currentposition;
	if(targetleg == kAnyLegMove)
	{
		if(targetposition - currentposition<CalDMMaxSafeDistance())return (targetposition - currentposition);
		float resultbuf1=0,resultbuf2 = 0;
		required_step_number = CalStepNumber(distance_all,distancehope,0,&resultbuf1);
		required_step_number = CalStepNumber(distance_all,distancehope,0,&resultbuf2);
		result = CompareMax(resultbuf1,resultbuf2);
	}
	if(targetleg == kLegState)
	{
		if(targetposition - currentposition<CalDMMaxSafeDistance())return (targetposition - currentposition);
	  required_step_number = CalStepNumber(distance_all,distancehope,0,&result);
	}
	else
	{
		if(targetposition - currentposition<CalDMMaxSafeDistance())return (targetposition - currentposition);
		required_step_number = CalStepNumber(distance_all,distancehope,1,&result);
	}
	return result;
}

int MyFloor(float value)
{
	int integerbuf = (int)value;
		return integerbuf;
}

int MyCeil(float value)
{
	int integerbuf = (int)value;
		return integerbuf+1;
		return integerbuf;
}

int MyClose(float value)
{
		int integerbuf = (int)value;
	float decimalbuf = value - integerbuf;
	if(decimalbuf>=0.5f)
	{
		return integerbuf+1;
	}
	else
	{
		return integerbuf;
	}
}

float CompareMax(float value1,float value2)
{
	if(value1>value2)return value1;
	return value2;
}
float CompareMin(float value1,float value2)
{
	if(value1>value2)return value2;
	return value1;
}