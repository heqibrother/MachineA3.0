#ifndef __LEG_MOVEMENT_H
#define __LEG_MOVEMENT_H

#include "movement.h"

/***�˶����ȵ�ģʽ***/
enum LegState {//��״̬
    kHighLegMove,//�����ƶ��������ڵ�
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