#ifndef __TESTMODE_H
#define __TESTMODE_H

#include "superstratum.h"


/***A车测试状态***/
typedef enum
{
	kWaitDebug,//等待调试
	kTestVelocityCurveWithoutChangeLeg,//测试速度波形
	kTestMotorLocation,//测试电机定位
	kTestStepDistanceCal,//测试定位步距计算是否准确
	kTestFunctionCalStepDistance,//测试函数
	kTestFunctionCrossRope = 5,
	kTestCommuniction,
}MachineATestItem;

extern MachineATestItem kMachineATestItem;
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
void TestFirstRedLine();
void TestSecondRedLine();
void TestClamberMode();
#endif