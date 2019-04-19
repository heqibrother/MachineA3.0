/*
   Responsible for overall planning and dispatching
*/
#include "plan.h"

void MakePlan()
{
	
}

void SetBasicMotionParameters(float targetpositiondistance,float targetpositionspeed,float targetyaw,int speedmode)
{
	DM_MoveInfo.distance_data.target_distance = targetpositiondistance/2;
	DM_MoveInfo.speed_data.target_position_speed = targetpositionspeed;
	leg_angle.target_yaw = targetyaw;
	DM_MoveInfo.speed_data.speed_mode = speedmode;
	DM_MoveInfo.motor_position = false;
}

//void SettingObstacleCrossingParameters(bool )
//{
//	
//}