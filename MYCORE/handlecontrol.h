#ifndef __HANDLECONTROL_H
#define __HANDLECONTROL_H

#include "superstratum.h"

/***����״̬***/
typedef enum
{
	kCommonState,
  kInitialPositionRestart,
	kFirstLinePositionRestart,
	kSecondLinePositionRestart,
	kClamberPositionRestart
}RestartCommand;

/***�ֱ���������***/
typedef struct
{
  int16_t sendhandledata[4];
}SendHandle;

/***�ֱ�״̬***/
typedef struct
{
	RestartCommand hRestartCommand;
  SendHandle send_handle;
}HandleCommand;

extern HandleCommand handle_command;
/*********Function declaration*******/

#endif