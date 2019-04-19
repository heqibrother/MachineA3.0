#ifndef __LEG_MOVEMENT_H
#define __LEG_MOVEMENT_H

#include "movement.h"

/***运动中腿着地的模式***/
enum LegState {//腿状态
    kHighLegMove,//高腿移动，矮腿在地
	  kLowLegMove
};

/***运动中腿的数据***/
typedef struct 
{
  int leg_state_number;
	int leg_target_state_time;
	int leg_safe_to_laydown;//1安全 0不安全
}LegStateData;
///***运动中腿高低的模式***/
//enum LegHeightState {//腿状态
//    kLegNothing,
//	  kLegWaitToStart,
//	  
//};

extern enum LegState kLegState;
extern LegStateData leg_state_data;
/*********Function declaration*******/
bool DetectLegRecoverPosition();
bool DetectLegLayDownPosition();
bool LegPartAnswer();
bool TimeToLayDown();

void LegModeChange();
void LayDown();

void HighlegLift();
void LowlegLift();
void ChangeLeg(short I1, short I2,short I3,short I4);
void LegPartInit();
#endif