#ifndef __LEG_MOVEMENT_H
#define __LEG_MOVEMENT_H

#include "movement.h"

/***�˶������ŵص�ģʽ***/
enum LegState {//��״̬
    kHighLegMove,//�����ƶ��������ڵ�
	  kLowLegMove
};

/***�˶����ȵ�����***/
typedef struct 
{
  int leg_state_number;
	int leg_target_state_time;
	int leg_safe_to_laydown;//1��ȫ 0����ȫ
}LegStateData;
///***�˶����ȸߵ͵�ģʽ***/
//enum LegHeightState {//��״̬
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