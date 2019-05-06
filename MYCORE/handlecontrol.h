#ifndef __HANDLECONTROL_H
#define __HANDLECONTROL_H

#include "math.h"
#include "stm32f4xx.h"
#include "arm_math.h"
#include <stdbool.h>

/***����״̬***/
typedef enum
{
	kCommonState,
  kInitialPositionRestart,
	kFirstLinePositionRestart,
	kSecondLinePositionRestart,
	kClamberPositionRestart,
	kShowRedFieldTurnLeft,
}RestartCommand;

/***�ֱ���������***/
typedef struct
{
  int16_t sendhandledata[4];
	bool send_field_para_y_flag;
}SendHandle;

/***�ֱ�״̬***/
typedef struct
{
	RestartCommand hRestartCommand;
  SendHandle send_handle;
}HandleCommand;

extern HandleCommand handle_command;

#include "superstratum.h"
/*********Function declaration*******/
void SendFieldParaY();
#endif