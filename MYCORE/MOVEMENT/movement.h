#ifndef __MOVEMENT_H
#define __MOVEMENT_H

#include "math.h"
#include "stm32f4xx.h"
#include "arm_math.h"
#include <stdbool.h>
#include "superstratum.h"
#include "DM_motor_movement.h"
#include "RM_motor_movement.h"
#include "leg_movement.h"

/***�˶�ģʽ������***/
typedef enum 
{
	kSpeedFirst,
	kLocationFirst
}MovementStyle;

/***�˶���Ϣ�Ľṹ***/
typedef  struct 
{
  float initial_position;
	float end_position;
	float target_speed;
	int speed_mode;
	int32_t start_time;
	float obstacle_location;
	float obstacle_width;
	bool motor_position;
}MotorMoveState;

/***���ٶ�Ϊ���ȵ�ö��ʱ�����***/
//typedef enum{                //�ٶ����ȵ�ʱ���־λ
//	  kSBeforeFurtherPlan,     //�������ϸ�Ĳ���
//	  kSBeforeRecoverLeg,      //δ����������
//    kSBeforeRiseItself,      //δ����������ָ���߶�
//	  kSBeforeLayDownLegs,     //δ������λ��
//	  kSBeforeDMPosition,      //ֱ�е��δ��λ
//	  kSAllDone                //���в����������
//}TimePointForSpeed;

///***�Զ�λΪ���ȵĿ��ƽṹ***/
//typedef enum{                //��λ���ȵ�ʱ���־λ
//	  kLBeforeFurtherPlan,     //���������ϸ�Ĳ���
//	  kLBeforeRecoverLegAndRiseItself,  //δ��������������δ����������ָ���߶�
//	  kLBeforeSelfCorrection,  //δ�����Ծ���
//	  kLBeforeDRMPosition,     //ֱ�е������תδ��λ
//	  kLAllDone                //���в����������
//}TimePointForLocation;

/***�Զ�λΪ���ȵĿ��ƽṹ***/
typedef enum{                //ȫ��ʱ���־λ
	  kBeforeFurtherPlan,     //�������ϸ�Ĳ���
	  kBeforeRecoverLeg,      //δ����������
    kBeforeRiseItself,      //δ����������ָ���߶�
	  kBeforeLayDownLegs,     //δ������λ��
  	kBeforeSelfCorrection,  //δ�����Ծ���
	  kBeforeDMPosition,      //ֱ�е��δ��λ
	  kBeforeRMPosition,      //��ת���δ��λ
	  kBeforeLegTouchGround,  //���ȴ���
	  kAllDone                //���в����������
}TimePoint;

/*********Function declaration*******/
bool ExcutePlan();
void SpeedFirstMode();
void LocationFirstMode();
void CalculateFurtherMovementData();
#endif
