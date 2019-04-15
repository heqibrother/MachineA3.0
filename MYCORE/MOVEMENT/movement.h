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

/***运动模式的类型***/
typedef enum 
{
	kSpeedFirst,
	kLocationFirst
}MovementStyle;

/***运动模式的类型***/
typedef enum 
{
	kCommonSine,
	kSineCosineCombination
}SpeedMode;

/***运动信息的结构***/
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

/***以速度为优先的枚举时点变量***/
//typedef enum{                //速度优先的时点标志位
//	  kSBeforeFurtherPlan,     //计算更详细的参数
//	  kSBeforeRecoverLeg,      //未把腿收起来
//    kSBeforeRiseItself,      //未把身体升到指定高度
//	  kSBeforeLayDownLegs,     //未到放腿位置
//	  kSBeforeDMPosition,      //直行电机未到位
//	  kSAllDone                //所有操作均已完成
//}TimePointForSpeed;

///***以定位为优先的控制结构***/
//typedef enum{                //定位优先的时点标志位
//	  kLBeforeFurtherPlan,     //计算更加详细的参数
//	  kLBeforeRecoverLegAndRiseItself,  //未把腿收起来并且未把身体升到指定高度
//	  kLBeforeSelfCorrection,  //未进行自纠错
//	  kLBeforeDRMPosition,     //直行电机、旋转未到位
//	  kLAllDone                //所有操作均已完成
//}TimePointForLocation;

/***以定位为优先的控制结构***/
typedef enum{                //全部时点标志位
	  kBeforeFurtherPlan,     //计算更详细的参数
	  kBeforeRecoverLeg,      //未把腿收起来
    kBeforeRiseItself,      //未把身体升到指定高度
	  kBeforeLayDownLegs,     //未到放腿位置
  	kBeforeSelfCorrection,  //未进行自纠错
	  kBeforeDMPosition,      //直行电机未到位
	  kBeforeRMPosition,      //旋转电机未到位
	  kBeforeLegTouchGround,  //放腿触地
	  kAllDone                //所有操作均已完成
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
