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

/***A�����״̬***/
typedef enum
{
  kWaitToStart,//û���κδ���
	kNormalWalk,//��������
	kNeedToRestart,//�����˼�ͣ���ָ�������̬
	kWaitToRestart,//�Ѿ��ָ�������̬���ȴ���������
	kTestMode,//����ģʽ
	kMachineError,//����
}MachineAGeneralState;

/***A���н��׶�***/
typedef enum{        //A��״̬
    kBeforeStart = 0,      	//����ǰ
    kStart,                 //������ȫ��ǰ��
    kBeforeLaserDetect,     //���뼤��̽�ⷶΧ��׼���������ࣩ
	  kBeforeTurnLeft,        //�������ൽǡ�ÿ���ת��
	  kTurnLeft,              //��һ��ת��
	  kBothLegTurnLeft = 5,   //�������
	  kBeforeStepUp,          //ǰ����̽��̨��λ�ã�̽�⵽̨�׽�����һ��
	  kStepUp,                //�������ൽָ��λ��
	  kClimbOverTheStep,      //�̶����師Խ��̨��
	  kBeforeTurnRight,       //һֱ�ߣ���������׼���ڶ���ת��
	  kTurnRight = 10,        //�ڶ���ת��
	  kBothLegTurnRight,      //�������
	  kBeforeCrossTheFirstRope,//��������׼��Խ����һ����
	  kCrossTheFirstRope,     //��ǰ���������
	  kBeforeCrossTheSecondRope,//��������׼��Խ����һ����
	  kCrossTheSecondRope =15,//��ǰ���������
	  kArriveThePost,          //ǰ���ִ���վ
	  kStopAtPost,             //ֹͣ����վ
	  kClamberMode,            //�л������³�ʼ��״̬
	  kClamberReady,           //�ȴ�����ָ��
	  kClamber = 20,           //����״̬
	  kReachSummit,            //�Ƕ�
		kStop,                   //ͣ��
		kFault,                   //����״̬��׼������
		kRestartPrepare,          //����״̬׼��
		kWaitToBeAwaken =25           //�ȴ�����׼��
}MachineAState;

/***A����������***/
typedef struct
{
	int total_step_number;//��¼�ж��ܲ���
	int stage_step_number;//��¼���ߵ�ÿһ���׶εĲ���
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
#endif