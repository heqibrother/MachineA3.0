#ifndef __SECURITYDETECTION_H
#define __SECURITYDETECTION_H

#include "superstratum.h"
#include "LED.h"
/***安全指示灯参数***/
typedef struct 
{
  bool state;
	int32_t change_dark_time;
	int32_t change_light_time;
	int32_t light_time;
	int32_t dark_time;
	int32_t change_time;
}SecurityLedState;

/***安全状态***/
typedef enum 
{
	kSecurityConfirm,//知道安全
	kSecurityDestroyed,//知道不安全
	kSecurityUnknow,//不知是否安全
	kSecurityProblem,//十分危险
	kStopJudgeSecurity,//关闭判断
}SecurityState;

/***安全项目信息***/
typedef struct 
{
  SecurityState State;
  int32_t last_time_confirm_security;
	bool refresh_flag;
}SecurityItemData;

/***安全项目列举***/
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