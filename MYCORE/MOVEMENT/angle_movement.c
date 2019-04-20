#include "angle_movement.h"


LegAngle leg_angle;

void LegYawInit()
{
	leg_angle.highleg_yaw = 0;
	leg_angle.lowleg_yaw = 0;
	leg_angle.target_yaw = 0;
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