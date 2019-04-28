/*
   Responsible for overall planning and dispatching
*/
#include "plan.h"

void MakePlan()
{
	switch(kMachineAGeneralState)
	{
		case kStartingPre:
			StartPreMode();
			break;
		
		case kNormalWalk:
			if(LastWalkOver())
			{
				WalkPlan();
				machineA_general_data.plan_isok = true;
			}
			break;
			
		case kClamberModeWaiting:
			LegPrepareForClamber();
			break;
			
		case kNeedToRestart:
			
			break;
		
		case kWaitCommand:
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
	DM_MoveInfo.distance_data.target_distance = targetpositiondistance/2.0f;
	DM_MoveInfo.speed_data.target_position_speed = targetpositionspeed;
	leg_angle.target_yaw = targetyaw;
	DM_MoveInfo.speed_data.speed_mode = speedmode;
	movement_style = movementstyle;
	DM_MoveInfo.motor_position = false;
	RM_MoveInfo.motor_position = false;
	RM_speed_stage = kStopMove;
	DM_speed_stage = kStopMove;
	time_point = kBeforeFurtherPlan;
}

bool LastWalkOver()
{
	if(time_point == kAllDone)
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