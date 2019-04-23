#include "angle_movement.h"


LegAngle leg_angle;

void LegYawInit()
{
	leg_angle.highleg_yaw = 0;
	leg_angle.lowleg_yaw = 0;
	leg_angle.target_yaw = 0;
	leg_angle.initial_yaw = leg_angle.original_yaw;
}

float CalYaw()
{
	float result = 0;
		result = leg_angle.original_yaw - leg_angle.initial_yaw;
		while(result>180)
		{
			result = result -360;
		}
		while(result<-180)
		{
			result = result + 360;
		}
	return result;
}

void RefreshLegYaw()
{
	leg_angle.lowleg_yaw = CalYaw();
	leg_angle.highleg_yaw = leg_angle.lowleg_yaw -  (RotateMotor.PositionMeasure -RM_MoveInfo.position_data.initial_position)*RM_radio;
	if(kLegState == kHighLegMove)
	{
		leg_angle.groundleg_yaw = leg_angle.lowleg_yaw;
		leg_angle.suspendleg_yaw = leg_angle.highleg_yaw;
	}
	else if(kLegState == kLowLegMove)
	{
		leg_angle.groundleg_yaw = leg_angle.highleg_yaw;
		leg_angle.suspendleg_yaw = leg_angle.lowleg_yaw;
	}
}