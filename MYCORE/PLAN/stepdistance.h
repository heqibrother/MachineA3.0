#ifndef __STEPDISTANCE_H
#define __STEPDISTANCE_H

#include "plan.h"

/*********Function declaration*******/
int MyClose(float value);
int MyFloor(float value);
int MyCeil(float value);
float CompareMax(float value1,float value2);
float CompareMin(float value1,float value2);
int CalStepNumber(float alldistance,float distancehope,int required_remainder,float *step_distance);
float CalStepDistance(float targetposition,float currentposition,float distancehope,LegState targetleg);
#endif