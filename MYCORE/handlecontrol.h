#ifndef __HANDLECONTROL_H
#define __HANDLECONTROL_H

#include "math.h"
#include "stm32f4xx.h"
#include "arm_math.h"
#include <stdbool.h>

/***重启状态***/
typedef enum
{
	kCommonState,
  kInitialPositionRestart,
	kFirstLinePositionRestart,
	kSecondLinePositionRestart,
	kClamberPositionRestart,
	kShowRedFieldTurnLeft,
}RestartCommand;

/***手柄返回数据***/
typedef struct
{
  int16_t sendhandledata[4];
	bool send_field_para_y_flag;
}SendHandle;

/***手柄状态***/
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