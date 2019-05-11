#ifndef __SECURITYDETECTION_H
#define __SECURITYDETECTION_H

#include "superstratum.h"
#include "LED.h"
/***��ȫָʾ�Ʋ���***/
typedef struct 
{
  bool state;
	int32_t change_dark_time;
	int32_t change_light_time;
	int32_t light_time;
	int32_t dark_time;
	int32_t change_time;
}SecurityLedState;

/***��ȫ״̬***/
typedef enum 
{
	kSecurityConfirm,//֪����ȫ
	kSecurityDestroyed,//֪������ȫ
	kSecurityUnknow,//��֪�Ƿ�ȫ
	kSecurityProblem,//ʮ��Σ��
	kStopJudgeSecurity,//�ر��ж�
}SecurityState;

/***��ȫ��Ŀ��Ϣ***/
typedef struct 
{
  SecurityState State;
  int32_t last_time_confirm_security;
	bool refresh_flag;
}SecurityItemData;

/***��ȫ��Ŀ�о�***/
typedef struct 
{
  SecurityItemData sGeneralState;
	SecurityItemData sMotorState;
	SecurityItemData sLegState;
	SecurityItemData sGyroscope;
	SecurityItemData RotateMotor;
}SecurityItems;

extern SecurityItems securityitem;
extern SecurityLedState RedState,GreenState,BlueState;
/*********Function declaration*******/
void JudgeSecurityState();
SecurityState JudgeGeneralStateSecurity();
SecurityState JudgeMotorStateSecurity();
SecurityState JudgeLegState();
SecurityState JudgeRotateMotorSecurity();
SecurityState JudgeGyroscopeSecurity();
void SecurityStateInit();
void SetTwinkParameter(SecurityState state,SecurityLedState *ledstate);
void LedIndicate(LED_TypeDef led,SecurityLedState *ledstate,int32_t current_time);
#endif