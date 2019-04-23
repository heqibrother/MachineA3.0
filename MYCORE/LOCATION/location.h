#ifndef __LOCATION_H
#define __LOCATION_H

#include "superstratum.h"


/***��ȡ����Ľṹ***/
typedef struct 
{
  float x;
	float y;
	int32_t time;//��ȡʱ��
	bool ShouldBeTrusted;//���ű�־���������γ̶�
}LocationDataType;

/***��������ṹ***/
typedef struct 
{
  float highleg_x;
	float highleg_y;
	float lowleg_x;
	float lowleg_y;
	float ground_leg_x;//�ŵ�������
	float ground_leg_y;
	float suspend_leg_x;//����������
	float suspend_leg_y;
}PositionDataType;

/***A������***/
typedef struct 
{
  LocationDataType relative_position;
  LocationDataType laser_radar_position;
	LocationDataType laser1_position;
	
	PositionDataType current_position;
  PositionDataType motor_position;
	
	//��ȡ�����ԭʼ����
	float laser1_data;
	float laser_radar_data_x;
	float laser_radar_data_y;
	float relative_data_x;
	float relative_data_y;
	
	float ground_leg_after_step;//ǰ��
	float ground_leg_before_step;//����
	float suspend_leg_before_step;
}LocationData;

extern LocationData location_data;

#include "size_map.h"
#include "locationinfo.h"
#include "localcomputing.h"
/*********Function declaration*******/
/**
 * @brief: Refresh location information
 * @return: none
 * @status: 2019.4.21
 */
void RefreshLocation();

/**
 * @brief: Record the position of the ground leg and the suspended leg
 * @return: none
 * @status: 2019.4.21
 */
void RecordLocation();

/**
 * @brief: Send the information needed by the computer
 * @return: none
 * @status: 2019.4.21
 */
void SendPCMessage(short I1, short I2,short I3,short I4,short I5, short I6,short I7,short I8);

void PositionInit();
#endif