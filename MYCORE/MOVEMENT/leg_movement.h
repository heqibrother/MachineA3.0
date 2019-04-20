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
	int leg_state_number_pre;
	int leg_target_state_time;
	int leg_safe_to_laydown;//1��ȫ 0����ȫ
}LegStateData;

/***�˶����ȷ��ص�����***/
typedef struct 
{
	int16_t leg_state_[4] ;
	int leg_state_feedback;
	bool crossed_step ;
}LegDataFeedback;

///***�˶����ȸߵ͵�ģʽ***/
//enum LegHeightState {//��״̬
//    kLegNothing,
//	  kLegWaitToStart,
//	  
//};

extern enum LegState kLegState;
extern LegStateData leg_state_data;
extern LegDataFeedback leg_data_feedback;
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
int32_t GetTimeLayDownAdvance();
#endif