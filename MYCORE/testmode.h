#ifndef __TESTMODE_H
#define __TESTMODE_H

#include "superstratum.h"


/***A������״̬***/
typedef enum
{
	kWaitDebug,//�ȴ�����
	kTestVelocityCurveWithoutChangeLeg,//�����ٶȲ���
	kTestMotorLocation,//���Ե����λ
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

#endif