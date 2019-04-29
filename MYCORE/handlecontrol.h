#ifndef __HANDLECONTROL_H
#define __HANDLECONTROL_H

#include "superstratum.h"

/***重启状态***/
typedef enum
{
	kCommonState,
  kInitialPositionRestart,
	kFirstLinePositionRestart,
	kSecondLinePositionRestart,
	kClamberPositionRestart
}RestartCommand;

/***手柄返回数据***/
typedef struct
{
  int16_t sendhandledata[4];
}SendHandle;

/***手柄状态***/
typedef struct
{
	RestartCommand hRestartCommand;
  SendHandle send_handle;
}HandleCommand;

extern HandleCommand handle_command;
/*********Function declaration*******/

#endif