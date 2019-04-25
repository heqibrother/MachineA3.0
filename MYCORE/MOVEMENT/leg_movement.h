#ifndef __LEG_MOVEMENT_H
#define __LEG_MOVEMENT_H
#include "stm32f4xx.h"
#include <stdbool.h>
#include "movement.h"

extern LegState kLegState;
extern LegStateData leg_state_data;
extern LegDataFeedback leg_data_feedback;
extern LegState ChangeLegState(LegState klegstate);

/*********Function declaration*******/
bool DetectLegRecoverPosition();
bool DetectLegLayDownPosition();
bool DetectLegAllPosition();
bool LegPartAnswer();
bool TimeToLayDown();

void LegModeChange();
void LayDown();

void HighlegLift();
void LowlegLift();
//void ChangeLeg(short I1, short I2,short I3,short I4);
void LegPartInit();
int32_t GetTimeLayDownAdvance();
void SendLegCommand();
void LegPrepareForClamber();
void SetLegLengthHigh(int16_t legrightfront,int16_t legleftfront,int16_t legleftbehind,int16_t legrightbehind);
void SetLegLengthLow(int16_t legrightfront,int16_t legleftfront,int16_t legleftbehind,int16_t legrightbehind);
void SendLegLength();
void ClamberModeLeg();
LegState DetectLegState();
void SteadyLegMode();
#endif