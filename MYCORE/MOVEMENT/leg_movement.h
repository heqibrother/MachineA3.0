#ifndef __LEG_MOVEMENT_H
#define __LEG_MOVEMENT_H

#include "movement.h"

/***运动中腿的模式***/
enum LegState {//腿状态
    kHighLegMove,//高腿移动，矮腿在地
	  kLowLegMove
};

extern enum LegState kLegState;
/*********Function declaration*******/
bool DetectLegRecoverPosition();
bool DetectLegLayDownPosition();
bool LegPartAnswer();
bool TimeToLayDown();

void LegModeChange();
void LayDown();

#endif