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
#include "testmode.h"
#include "securitydetection.h"
#include "gadget.h"

/***A车宏观状态***/
typedef enum
{
  kWaitToStart,//没有任何触发
	kStartingPre,
	kNormalWalk,//正常行走
	kClamberModeWaiting,//处于上坡前的等待模式，等待启动
	kNeedToRestart,//触发了急停，恢复重启姿态
	kWaitToRestart,//已经恢复重启姿态，等待触发启动
	kWaitCommand = 5,//等待指令
	kTestMode,//测试模式
	kMachineError,//报错
}MachineAGeneralState;

/***划分阶段***/
typedef enum
{
  kStage1,
  kStage2,
	kStage3,
	kStage4,
	kStage5,
	kStage6,
}Stage;

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

/***A车总体数据***/
typedef struct
{
	int total_step_number;//记录行动总步数
	int stage_step_number;//记录行走的每一个阶段的步数
	bool plan_isok;
	int32_t start_time;
	Stage stage;
}MachineAGeneralData;

extern MachineAGeneralState kMachineAGeneralState;
extern MachineAState kMachineAState;
extern MachineAGeneralData machineA_general_data;
/*********Function declaration*******/
/**
 * @brief: Routinely perform data update tasks
 * @return: none
 * @status: 2019.4.21
 */
void UpdateInformation();

/**
 * @brief: Judge whether to end a step or not, and execute a movement if not.
 * @return: none
 * @status: 2019.4.21
 */
void JudgeMovement();

/**
 * @brief: Detect vehicle status for trigger switch
 * @return: none
 * @status: 2019.4.14
 */
void CheckState();

/**
 * @brief:  Initialize status flag at the very beginning
 * @return: none
 * @status: 2019.4.21
 */
void StateInit();

/**
 * @brief: State Initialization Before Machine Motion
 * @return: none
 * @status: 2019.4.21
 */
void CompetitionInit();

/**
 * @brief: Running the Formal Competition Mode
 * @return: none
 * @status: 2019.4.22
 */
void CompetitionMode();

void FormalStart();
#endif