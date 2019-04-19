#ifndef __ANGLE_MOVEMENT_H
#define __ANGLE_MOVEMENT_H
#include "movement.h"

/***四足腿的角度数据***///因为在其他.h文件已经引用到了这个结构体，所以就放在include头文件之上编译，避免错误
typedef struct 
{
  float highleg_yaw;
	float lowleg_yaw;
	float target_yaw;
}LegAngle;

extern LegAngle leg_angle;
extern const float RM_angle_min;
extern const float RM_angle_max;





/*********Function declaration*******/
void LegYawInit();

#endif