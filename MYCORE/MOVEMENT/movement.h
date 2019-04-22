#ifndef __MOVEMENT_H
#define __MOVEMENT_H

#include "math.h"
#include "stm32f4xx.h"
#include "arm_math.h"
#include <stdbool.h>


/***运动模式的类型***/
typedef enum 
{
	kSpeedFirst,//速度优先模式，直行电机到位优先，用于直行段
	kLocationFirst//定位优先模式，确保稳定性，用于踩准步伐，跨绳，台阶等
}MovementStyle;

/***运动模式的类型***/
typedef enum 
{
  kOnlyAccelerateStability,//只延长加速段
	kOnlyDecelerateStability,//只延长减速段
	kBothStability,          //加速段减速段都延长
	kBothUnStablity          //正常，都不延长
}SpeedMode;//决定加减速时间

/***电机运动位置数据（角度为单位）***/
typedef struct 
{
  float initial_position;//记录腿零点时的电机角度值（标准时刻，两腿重合）
	
	float start_position;//每步开始的位置
	float finish_accelerate_position;//计算的电机值节点
	float finish_keepspeed_position;
	float finish_decelerate_position;
	
	float current_position;
	float record_position;
	float position_walked;
	float position_left;
}MotorPositionData;

/***电机运动绝对距离数据（毫米为单位）***/
typedef struct 
{
	float target_distance;
	float distance_accelerate;
	float distance_decelerate;
	float distance_walked;//已走距离
	float distance_left;
	float distance_all;

}MotorDistanceData;

/***电机运动时间数据（阶段总时间）***/
typedef struct 
{
	int32_t start_time;//每步开始的时间
	int32_t accelerate_time;
	int32_t keepspeed_time;
	int32_t decelerate_time;
}MotorTimeData;

/***电机运动速度数据***/
typedef struct 
{
	float target_position_speed;//以电机角度为单位
	float target_distance_speed;
	float current_expected_speed;
	float speed_direction;//高矮腿切换，速度方向取反系数
	SpeedMode speed_mode;
}MotorSpeedData;

/***障碍的位置信息***/
typedef struct 
{
  bool obstacle_exist;//判断这一步是否存在障碍
  //障碍位置是实际位置，和电机运行有两倍关系
	float obstacle_location;
	float obstacle_width;
}Obstacle;

/***运动信息的结构***/
typedef  struct 
{
	MotorPositionData position_data;
  MotorDistanceData distance_data;
  MotorTimeData time_data;
  MotorSpeedData speed_data;
	bool motor_position;//标志位，判断电机是否到位
}MotorMoveState;

/***控制结构，所有时点***/
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

/***运动中腿着地的模式***/
typedef enum {//腿状态
    kHighLegMove,//高腿移动，矮腿在地
	  kLowLegMove,
	  kAnyLegMove
}LegState;

/***运动中腿的数据***/
typedef struct 
{
	int leg_state_command;//发给腿的指令，控制是否伸缩
  int leg_state_number;//当时正发给腿的状态数据
	int leg_state_number_pre;//记录状态数据，用于腿切换时点的切换
	int leg_target_state_time;//记录到下一个状态的时间
	int leg_safe_to_laydown;//1安全 0不安全
}LegStateData;

/***运动中腿返回的数据***/
typedef struct 
{
	int16_t leg_state_[4] ;//记录每条腿的状态，顺序右前逆时针到右后
	int leg_state_feedback;//返回的腿状态
	int crossd_step_state;
	bool crossed_step ;//判断是否越过台阶
}LegDataFeedback;

//下置引用，确保应用中调用结构体时，结构体已经被声明
#include "superstratum.h"
#include "DM_motor_movement.h"
#include "RM_motor_movement.h"
#include "leg_movement.h"
#include "movement_basic_math.h"
#include "angle_movement.h"

extern MotorMoveState DM_MoveInfo,RM_MoveInfo;
extern MovementStyle movement_style;
extern TimePoint time_point_for_speed,time_point_for_location;
extern Obstacle obstacle1,obstacle2;
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

/**
 * @brief: Refresh the previous record before each step starts
 * @status: 2019.4.21
 */
void RefreshMovementDataEveryBegining();

/**
 * @brief: Determine whether you need to wait for your legs to be lifted in place
 * @return: true(need to wait) false(no)
 * @status: 2019.4.21
 */
bool SafeToMoveBeforeRecover();

/**
 * @brief: Determine if you need to wait for your legs to cross the barrier before putting them down
 * @return: true(need to wait) false(no)
 * @status: 2019.4.21
 */
bool SafeToLayDownBeforePosition();

/**
 * @brief: Detect errors in the initial decision based on location
 * @return: none
 * @status: 2019.4.21
 */
void SelfCorrection();

/**
 * @brief: set obstacles in one step
 * @param: position of obstacles , width of obstacles
 * @return: none
 * @status: 2019.4.21
 */
void SetObstacleLocation(float obstacleposition,float obstaclewidth,Obstacle *targetobstacle);

/**
 * @brief: Update regular motion data
 * @return: none
 * @status: 2019.4.21
 */
void RefreshMovementData();
#endif
