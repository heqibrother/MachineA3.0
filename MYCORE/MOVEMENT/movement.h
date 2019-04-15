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
#include "movement_basic_math.h"

/***�˶�ģʽ������***/
typedef enum 
{
	kSpeedFirst,
	kLocationFirst
}MovementStyle;

/***�˶�ģʽ������***/
typedef enum 
{
	kCommonSine,
	kSineCosineCombination
}SpeedMode;

/***�˶���Ϣ�Ľṹ***/
typedef  struct 
{
  float initial_position;
	float finish_accelerate_position;
	float finish_keep_speed_position;
	float finish_decelerate_position;
	float end_position;
	float target_speed;
	SpeedMode speed_mode;
	int32_t start_time;
	int32_t accelerate_time;
	int32_t decelerate_time;
	float obstacle_location;
	float obstacle_width;
	bool motor_position;
	
	float distance_accelerate;
	float distance_decelerate;
	float distance_walked;
	float distance_left;
	float distance_all;
	float current_expected_speed;
	float speed_direction;
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


extern MotorMoveState DM_MoveInfo,RM_MoveInfo;
/*********Function declaration*******/

/**
 * @brief: Execute motion planning according to different time points
 * @return: false(continue) / true(finish)
 * @status: 2019.4.14
 */
bool ExcutePlan();

/**
 * @brief: Executing the motion of the speed-first time point
 * @return: none
 * @status: 2019.4.14
 */
void SpeedFirstMode();

/**
 * @brief: Executing the motion of the location-first time point
 * @return: none
 * @status: 2019.4.14
 */
void LocationFirstMode();

/**
 * @brief: Calculate more detailed motion thresholds based on the target
 * @status: 2019.4.14
 */
void CalculateFurtherMovementData();
#endif
