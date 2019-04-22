#ifndef __TESTMODE_H
#define __TESTMODE_H

#include "superstratum.h"


/***A车测试状态***/
typedef enum
{
	kWaitDebug,//等待调试
	kTestVelocityCurveWithoutChangeLeg//测试速度波形
}MachineATestItem;

/*********Function declaration*******/
/**
 * @brief: Test mode initialization
 * @return: none
 * @status: 2019.4.21
 */
void TestInit();

/**
 * @brief: Used for test module
 * @return: none
 * @status: 2019.4.21
 */
void TestMode();

#endif