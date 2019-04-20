#ifndef __MOVEMENT_H
#define __MOVEMENT_H

#include "math.h"
#include "stm32f4xx.h"
#include "arm_math.h"
#include <stdbool.h>


/***运动模式的类型***/
typedef enum 
{
	kSpeedFirst,
	kLocationFirst
}MovementStyle;

/***运动模式的类型***/
typedef enum 
{
  kOnlyAccelerateStability,
	kOnlyDecelerateStability,
	kBothStability,
	kBothUnStablity
}SpeedMode;//决定加减速时间

/***电机运动位置数据***/
typedef struct 
{
  float initial_position;//记录腿零点时的电机角度值（标准时刻，两腿重合）
	
	float start_position;
	float finish_accelerate_position;//计算的电机值节点
	float finish_keepspeed_position;
	float finish_decelerate_position;
	
	float current_position;
	float record_position;
	float position_walked;
	float position_left;
}MotorPositionData;

/***电机运动绝对距离数据***/
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

/***电机运动时间数据***/
typedef struct 
{
	int32_t start_time;
	int32_t accelerate_time;
	int32_t keepspeed_time;
	int32_t decelerate_time;
}MotorTimeData;

/***电机运动速度数据***/
typedef struct 
{
	float target_position_speed;
	float target_distance_speed;
	float current_expected_speed;
	float speed_direction;
	SpeedMode speed_mode;
}MotorSpeedData;

/***运动信息的结构***/
typedef  struct 
{
	MotorPositionData position_data;
  MotorDistanceData distance_data;
  MotorTimeData time_data;
  MotorSpeedData speed_data;
	bool motor_position;

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

//下置引用，确保应用中调用结构体时，结构体已经被声明
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
