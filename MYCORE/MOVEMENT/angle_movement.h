#ifndef __ANGLE_MOVEMENT_H
#define __ANGLE_MOVEMENT_H
#include "movement.h"

/***�����ȵĽǶ�����***///��Ϊ������.h�ļ��Ѿ����õ�������ṹ�壬���Ծͷ���includeͷ�ļ�֮�ϱ��룬�������
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