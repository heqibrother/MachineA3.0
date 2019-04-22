/*
   Responsible for overall planning and dispatching
*/
#include "plan.h"

void MakePlan()
{
	switch(kMachineAGeneralState)
	{
		case kNormalWalk:
			if(LastWalkOver())
			{
				WalkPlan();
				machineA_general_data.plan_isok = true;
			}
			break;
		
		default:
			break;
	}
}

void SetBasicMotionParameters(float targetpositiondistance,float targetpositionspeed,float targetyaw,SpeedMode speedmode,MovementStyle movementstyle)
{
	DM_MoveInfo.distance_data.target_distance = targetpositiondistance/2;
	DM_MoveInfo.speed_data.target_position_speed = targetpositionspeed;
	leg_angle.target_yaw = targetyaw;
	DM_MoveInfo.speed_data.speed_mode = speedmode;
	movement_style = movementstyle;
	DM_MoveInfo.motor_position = false;
	time_point_for_speed = kBeforeFurtherPlan;
	time_point_for_location = kBeforeFurtherPlan;
}

bool LastWalkOver()
{
	if(time_point_for_location == kAllDone || time_point_for_speed == kAllDone)
	{
		return true;
	}
	if(machineA_general_data.total_step_number==0)
	{
		machineA_general_data.total_step_number=1;
		return true;
	}
	return false;
}
//void SettingObstacleCrossingParameters(bool )
//{
//	
//}