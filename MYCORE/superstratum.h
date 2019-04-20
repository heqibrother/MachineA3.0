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
  kWaitToStart,
	kNormalWalk,
	kNeedToRestart,
	kWaitToRestart,
	kTestMode,
	kMachineError,
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

extern MachineAGeneralState kMachineAGeneralState;
extern MachineAState kMachineAState;
/*********Function declaration*******/
void UpdateInformation();
void JudgeMovement();
void CheckState();
void StateInit();
#endif