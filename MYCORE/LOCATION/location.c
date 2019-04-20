/*
   Responsible for overall locationing
*/
#include "location.h"
LocationData location_data;

void RefreshLocation()
{
		
}

void RecordLocation()
{
	if(kLegState == kHighLegMove)
	{
		location_data.current_position.ground_leg_x = location_data.current_position.lowleg_x;
		location_data.current_position.ground_leg_y = location_data.current_position.lowleg_y;
		location_data.current_position.suspend_leg_x = location_data.current_position.highleg_x;
		location_data.current_position.suspend_leg_y = location_data.current_position.highleg_y;
		location_data.motor_position.ground_leg_x = location_data.motor_position.lowleg_x;
		location_data.motor_position.ground_leg_y = location_data.motor_position.lowleg_y;
		location_data.motor_position.suspend_leg_x = location_data.motor_position.highleg_x;
		location_data.motor_position.suspend_leg_y = location_data.motor_position.highleg_y;
	}
	else if(kLegState == kLowLegMove)
	{
		location_data.current_position.ground_leg_x = location_data.current_position.highleg_x;
		location_data.current_position.ground_leg_y = location_data.current_position.highleg_y;
		location_data.current_position.suspend_leg_x = location_data.current_position.lowleg_x;
		location_data.current_position.suspend_leg_y = location_data.current_position.lowleg_y;
		location_data.motor_position.ground_leg_x = location_data.motor_position.highleg_x;
		location_data.motor_position.ground_leg_y = location_data.motor_position.highleg_y;
		location_data.motor_position.suspend_leg_x = location_data.motor_position.lowleg_x;
		location_data.motor_position.suspend_leg_y = location_data.motor_position.lowleg_y;
	}
}

