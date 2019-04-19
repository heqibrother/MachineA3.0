#ifndef __SUPERSTRATUM_H
#define __SUPERSTRATUM_H

#include "math.h"
#include "stm32f4xx.h"
#include "arm_math.h"
#include <stdbool.h>
#include "system_config.h"
#include "movement.h"
#include "plan.h"
#include "location.h"
#include "hust_math_lib.h"
#include "report_messages.h"

/***A³µºê¹Û×´Ì¬***/
typedef enum
{
  kWaitToStart,
	kNeedToRestart,
	kWaitToRestart,
	kTestMode,
	kMachineError,
}MachineAGeneralState;

extern const float Half_Length;
extern const float Half_Width;
/*********Function declaration*******/
void UpdateInformation();
void JudgeMovement();
void CheckState();
void StateInit();
#endif