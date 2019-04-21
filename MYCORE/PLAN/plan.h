#ifndef __PLAN_H
#define __PLAN_H

#include "superstratum.h"

#include "stepdistance.h"
#include "crossobstacles.h"
#include "walkplan.h"
/*********Function declaration*******/
void MakePlan();
void SetBasicMotionParameters(float targetpositiondistance,float targetpositionspeed,float targetyaw,SpeedMode speedmode,MovementStyle movementstyle);
bool LastWalkOver();

#endif