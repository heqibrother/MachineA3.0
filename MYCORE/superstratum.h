#ifndef __SUPERSTRATUM_H
#define __SUPERSTRATUM_H

#include "math.h"
#include "stm32f4xx.h"
#include "arm_math.h"
#include <stdbool.h>
#include "system_config.h"
#include "movement.h"
#include "plan.h"
#include "location.h"
#include "hust_math_lib.h"
#include "report_messages.h"

/***A车宏观状态***/
typedef enum
{
  kWaitToStart,
	kNormalWalk,
	kNeedToRestart,
	kWaitToRestart,
	kTestMode,
	kMachineError,
}MachineAGeneralState;

/***A车行进阶段***/
typedef enum{        //A车状态
    kBeforeStart = 0,      	//启动前
    kStart,                 //启动，全速前进
    kBeforeLaserDetect,     //进入激光探测范围（准备调整步距）
	  kBeforeTurnLeft,        //调整步距到恰好可以转向
	  kTurnLeft,              //第一次转向
	  kBothLegTurnLeft = 5,   //车体回正
	  kBeforeStepUp,          //前进，探测台阶位置，探测到台阶进入下一步
	  kStepUp,                //调整步距到指定位置
	  kClimbOverTheStep,      //固定三板斧越过台阶
	  kBeforeTurnRight,       //一直走，调整步距准备第二次转向
	  kTurnRight = 10,        //第二次转向
	  kBothLegTurnRight,      //车身回正
	  kBeforeCrossTheFirstRope,//调整步距准备越过第一根绳
	  kCrossTheFirstRope,     //当前步跨过绳子
	  kBeforeCrossTheSecondRope,//调整步距准备越过第一根绳
	  kCrossTheSecondRope =15,//当前步跨过绳子
	  kArriveThePost,          //前进抵达驿站
	  kStopAtPost,             //停止在驿站
	  kClamberMode,            //切换到上坡初始化状态
	  kClamberReady,           //等待上坡指令
	  kClamber = 20,           //上坡状态
	  kReachSummit,            //登顶
		kStop,                   //停车
		kFault,                   //故障状态，准备重启
		kRestartPrepare,          //重启状态准备
		kWaitToBeAwaken =25           //等待重启准备
}MachineAState;

extern MachineAGeneralState kMachineAGeneralState;
extern MachineAState kMachineAState;
/*********Function declaration*******/
void UpdateInformation();
void JudgeMovement();
void CheckState();
void StateInit();
#endif