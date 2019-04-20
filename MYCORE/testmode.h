#ifndef __TESTMODE_H
#define __TESTMODE_H

#include "superstratum.h"


/***A³µ²âÊÔ×´Ì¬***/
typedef enum
{
	kWaitDebug,
	kTestVelocityCurveWithoutChangeLeg
}MachineATestItem;

/*********Function declaration*******/
void TestInit();
void TestMode();

#endif