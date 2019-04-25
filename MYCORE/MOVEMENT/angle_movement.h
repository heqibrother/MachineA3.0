#ifndef __ANGLE_MOVEMENT_H
#define __ANGLE_MOVEMENT_H
#include "movement.h"

/***四足腿的角度数据***///因为在其他.h文件已经引用到了这个结构体，所以就放在include头文件之上编译，避免错误
typedef struct 
{
  float highleg_yaw;
	float lowleg_yaw;
	float groundleg_yaw;
	float suspendleg_yaw;
	float target_yaw;
	float initial_yaw;//陀螺仪初始绝对角度
	float original_yaw;//陀螺仪的值
	float original_pitch;
}LegAngle;

extern LegAngle leg_angle;






/*********Function declaration*******/
/**
 * @brief: Initialize the angle information and record the absolute angle at the beginning
 * @return: none
 * @status: 2019.4.21
 */
void LegYawInit();

/**
 * @brief: Obtaining the Relative Angle of Gyroscope
 * @return: yaw of lowleg(°)
 * @status: 2019.4.21
 */
float CalYaw();

/**
 * @brief: Refresh yaw of highleg and lowleg
 * @return: none
 * @status: 2019.4.22
 */
void RefreshLegYaw();

#endif