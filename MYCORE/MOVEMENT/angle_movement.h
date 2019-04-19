#ifndef __ANGLE_MOVEMENT_H
#define __ANGLE_MOVEMENT_H

/***四足腿的角度数据***///因为在其他.h文件已经引用到了这个结构体，所以就放在include头文件之上编译，避免错误
typedef struct 
{
  float highleg_yaw;
	float lowleg_yaw;
}LegAngle;

#include "movement.h"



/*********Function declaration*******/


#endif