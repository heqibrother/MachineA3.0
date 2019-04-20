#ifndef __MOVEMENT_H
#define __MOVEMENT_H

#include "math.h"
#include "stm32f4xx.h"
#include "arm_math.h"
#include <stdbool.h>


/***�˶�ģʽ������***/
typedef enum 
{
	kSpeedFirst,
	kLocationFirst
}MovementStyle;

/***�˶�ģʽ������***/
typedef enum 
{
  kOnlyAccelerateStability,
	kOnlyDecelerateStability,
	kBothStability,
	kBothUnStablity
}SpeedMode;//�����Ӽ���ʱ��

/***����˶�λ������***/
typedef struct 
{
  float initial_position;//��¼�����ʱ�ĵ���Ƕ�ֵ����׼ʱ�̣������غϣ�
	
	float start_position;
	float finish_accelerate_position;//����ĵ��ֵ�ڵ�
	float finish_keepspeed_position;
	float finish_decelerate_position;
	
	float current_position;
	float record_position;
	float position_walked;
	float position_left;
}MotorPositionData;

/***����˶����Ծ�������***/
typedef struct 
{
	float target_distance;
	float distance_accelerate;
	float distance_decelerate;
	float distance_walked;
	float distance_left;
	float distance_all;
	
	float obstacle_location;
	float obstacle_width;
}MotorDistanceData;

/***����˶�ʱ������***/
typedef struct 
{
	int32_t start_time;
	int32_t accelerate_time;
	int32_t keepspeed_time;
	int32_t decelerate_time;
}MotorTimeData;

/***����˶��ٶ�����***/
typedef struct 
{
	float target_position_speed;
	float target_distance_speed;
	float current_expected_speed;
	float speed_direction;
	SpeedMode speed_mode;
}MotorSpeedData;

/***�˶���Ϣ�Ľṹ***/
typedef  struct 
{
	MotorPositionData position_data;
  MotorDistanceData distance_data;
  MotorTimeData time_data;
  MotorSpeedData speed_data;
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

//�������ã�ȷ��Ӧ���е��ýṹ��ʱ���ṹ���Ѿ�������
#include "superstratum.h"
#include "DM_motor_movement.h"
#include "RM_motor_movement.h"
#include "leg_movement.h"
#include "movement_basic_math.h"
#include "angle_movement.h"

extern MotorMoveState DM_MoveInfo,RM_MoveInfo;
extern MovementStyle movement_style;
/*********Function declaration*******/

/**
 * @brief: Execute motion planning according to different time points
 * @return: false(continue) / true(finish)
 * @status: 2019.4.14
 */
bool ExecutePlan();

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
