/*
   To determine the timing of different motion control 
	 modes, it is mainly divided into speed-first and 
	 location-first timing control.
*/

#include "movement.h"

MotorMoveState DM_MoveInfo,RM_MoveInfo;
MovementStyle movement_style;
TimePoint time_point_for_speed,time_point_for_location;

bool ExcutePlan()
{
	switch(movement_style)
	{
		case kSpeedFirst:
			SpeedFirstMode();
		  if(time_point_for_speed == kAllDone)
			{
				return true;
			}
			break;
		
		case kLocationFirst:
			LocationFirstMode();
			if(time_point_for_location == kAllDone)
			{
				return true;
			}
			break;
		
		default:
			break;
	}
	return false;
}

void SpeedFirstMode()
{
	switch(time_point_for_speed)
	{
		case kBeforeFurtherPlan:
			CalculateFurtherMovementData();
			break;
		
		case kBeforeRecoverLeg:
			MoveDM();
		  MoveRM();
		  if(DetectLegRecoverPosition())
			{
				time_point_for_speed = kBeforeRiseItself;
			}
			break;
		
		case kBeforeRiseItself:
			MoveDM();
		  MoveRM();
		  LegModeChange();
		  if(LegPartAnswer())
			{
				time_point_for_speed = kBeforeLayDownLegs;
			}
			break;
		
		case kBeforeLayDownLegs:
			MoveDM();
		  MoveRM();
			if(TimeToLayDown())
			{
				LayDown();
				time_point_for_speed = kBeforeDMPosition;
			}
			break;
		
		case kBeforeDMPosition:
			MoveDM();
		  MoveRM();
		  if(DM_MoveInfo.motor_position&&DM_MoveInfo.motor_position)
			{
				time_point_for_speed = kBeforeLegTouchGround;
			}
			break;
			
		case kBeforeLegTouchGround:
			if(DetectLegLayDownPosition())
			{
				time_point_for_speed = kAllDone;
			}
			break;
		
		case kAllDone:
			break;
		
		default:
			break;
	}
}
		
void LocationFirstMode()
{
	
}

void CalculateFurtherMovementData()
{
	
}