#include "stepdistance.h"
int CalStepNumber(float alldistance,float distancehope,int required_remainder,float *step_distance,float deviation)
{
	int steps_far =0,steps_near = 0,steps_medium = 0,steps_result;
	steps_far = 2*MyCeil((alldistance - distancehope*(float)required_remainder)/(2.0f*(distancehope+deviation)));
	steps_medium = 2*MyClose((alldistance - distancehope*(float)required_remainder)/(2.0f*distancehope));
	steps_near =  2*MyFloor((alldistance - distancehope*(float)required_remainder)/(2.0f*(distancehope-deviation)));
	steps_result = MyClose(CompareMin((float)steps_medium,(float)steps_near));
	steps_result = MyClose(CompareMax((float)steps_far,(float)steps_result));
	(*step_distance) = (alldistance - distancehope*(float)required_remainder)/steps_result;
	if((*step_distance)<0.8*distancehope)
		(*step_distance) = (alldistance)/(float)(steps_result+required_remainder);
	return (steps_result+required_remainder);
}

float CalStepDistance(float targetposition,float currentposition,float distancehope,LegState targetleg,int *step_number_left,float safe_distance)
{
	float result = 0;
	int required_step_number = 0;
	//int required_remainder = 0;
	float distance_all = 0;
	distance_all = targetposition - currentposition;

	if(targetleg == kAnyLegMove)
	{
			if(targetposition-safe_distance<currentposition)
	{
			*step_number_left = 0;
		  return 0.0f;
	}
		if(targetposition - currentposition<distancehope+safe_distance)//CalDMMaxSafeDistance())
		{
			*step_number_left = 1;
			return (targetposition - currentposition);
		}
		float resultbuf1=0,resultbuf2 = 0;
		*step_number_left = MyClose(CompareMin((float)CalStepNumber(distance_all,distancehope,0,&resultbuf1,safe_distance)
			                  ,(float)CalStepNumber(distance_all,distancehope,1,&resultbuf2,safe_distance)));
		result = CompareMax(resultbuf1,resultbuf2);

	}
	if(targetleg != kLegState)//注意，此时悬空腿是还未走的，所以与目标落地腿相差偶数腿数
	{
			if(targetposition-safe_distance<currentposition)
	{
			*step_number_left = 0;
		  return 0.0f;
	}
		//if(targetposition - currentposition<500)return (targetposition - currentposition);
	  *step_number_left = CalStepNumber(distance_all,distancehope,0,&result,safe_distance);
	}
	else
	{
		if(targetposition - currentposition<distancehope+safe_distance)
		{
			*step_number_left = 1;
			return (targetposition - currentposition);
		}
		*step_number_left = CalStepNumber(distance_all,distancehope,1,&result,safe_distance);
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