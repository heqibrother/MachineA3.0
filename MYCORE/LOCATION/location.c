/*
   Responsible for overall locationing
*/
#include "location.h"
LocationData location_data,location_data_test;
int16_t laser_radar_message[4] = {0};

void RefreshLocation()
{
	
	RefreshCurrentPosition();
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

void SendLocationInfo()
{
	laser_radar_message[0] =  -1*field_direction*(current_field.first_column.x - location_data.motor_position.highleg_x);;
	laser_radar_message[1] = current_field.hill_position.y - CalOpositionY(installation.rplidar_position.x,installation.rplidar_position.y,kHighLegMove) - location_data.motor_position.highleg_y;
//laser_radar_message[1] = location_data.laser1_data;
	laser_radar_message[2] = leg_angle.highleg_yaw;
	SendPCData1((short)laser_radar_message[0],(short)laser_radar_message[1],(short)laser_radar_message[2],(short)field_direction);
	//SendPCData2((short)kMachineAState,(short)kMachineAGeneralState,(short)machineA_general_data.stage_step_number,(short)kLegState);
	short buf = current_field.hill_position.y - location_data.laser1_data * arm_cos_f32(GetLaseFieldAngle()*angle_to_radian_radio)
      	-CalOpositionY(installation.laser_position.x,installation.laser_position.y,kHighLegMove);//-55*(1.0f - (-1.0f)*field_direction)/2.0f;
	SendPCData2((short)kMachineAState,(short)kMachineAGeneralState,(short)buf,(short)(location_data.laser1_data * arm_cos_f32(GetLaseFieldAngle()*angle_to_radian_radio)));
  if(kMachineAGeneralState == kMachineError)
	{
		location_data.laser_correction_show = current_field.first_line_position.y - location_data.current_position.ground_leg_y;
	}
	else
	{
	  location_data.laser_correction_show = current_field.first_line_position.y - buf;
	}
	SendScreenData2(location_data.laser_correction_show,location_data.laser_correction,location_data.laser1_position.y,(short)MyClose(which_leg_first_clamber));
}

void PositionInit()
{
	location_data.current_position.lowleg_x = current_field.initial_position.x;
	location_data.current_position.lowleg_y = 0;
	location_data.laser_correction = 0;
	location_data.laser_correction_show = 0;
}
