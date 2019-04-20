#ifndef __LOCATION_H
#define __LOCATION_H

#include "superstratum.h"


/***获取坐标的结构***/
typedef struct 
{
  float x;
	float y;
	int32_t time;
	bool ShouldBeTrusted;
}LocationDataType;

/***机器坐标结构***/
typedef struct 
{
  float highleg_x;
	float highleg_y;
	float lowleg_x;
	float lowleg_y;
	float ground_leg_x;
	float ground_leg_y;
	float suspend_leg_x;
	float suspend_leg_y;
}PositionDataType;

/***A车坐标***/
typedef struct 
{
  LocationDataType relative_position;
  LocationDataType laser_radar;
	LocationDataType laser1_position;
	
	PositionDataType current_position;
  PositionDataType motor_position;
	
	float laser1_data;
	float laser_radar_data;
	float relative_data_x;
	float relative_data_y;
}LocationData;

extern LocationData location_data;

#include "size_map.h"
#include "locationinfo.h"
#include "localcomputing.h"
/*********Function declaration*******/
void RefreshLocation();
void RecordLocation();
#endif