#ifndef __ANGLE_MOVEMENT_H
#define __ANGLE_MOVEMENT_H
#include "movement.h"

/***�����ȵĽǶ�����***///��Ϊ������.h�ļ��Ѿ����õ�������ṹ�壬���Ծͷ���includeͷ�ļ�֮�ϱ��룬�������
typedef struct 
{
  float highleg_yaw;
	float lowleg_yaw;
	float groundleg_yaw;
	float suspendleg_yaw;
	float target_yaw;
	float initial_yaw;//�����ǳ�ʼ���ԽǶ�
	float original_yaw;//�����ǵ�ֵ
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
 * @return: yaw of lowleg(��)
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