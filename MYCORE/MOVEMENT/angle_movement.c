#include "angle_movement.h"

const float RM_angle_min = 3.0f;
const float RM_angle_max = 63.0f;
LegAngle leg_angle;

void LegYawInit()
{
	leg_angle.highleg_yaw = 0;
	leg_angle.lowleg_yaw = 0;
	leg_angle.target_yaw = 0;
}