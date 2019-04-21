/*
   To determine the timing of different motion control 
	 modes, it is mainly divided into speed-first and 
	 location-first timing control.
*/

#include "movement.h"

MotorMoveState DM_MoveInfo,RM_MoveInfo;
MovementStyle movement_style;
TimePoint time_point_for_speed,time_point_for_location;

bool ExecutePlan()
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
		  time_point_for_speed = kBeforeRecoverLeg;
			break;
		
		case kBeforeRecoverLeg:
			MoveDM();
		  MoveRM();
	//	  if(DetectLegRecoverPosition())
			{
				time_point_for_speed = kBeforeRiseItself;
			}
			break;
		
		case kBeforeRiseItself:
			MoveDM();
		  MoveRM();
		  LegModeChange();
	//	  if(LegPartAnswer())
			{
				time_point_for_speed = kBeforeLayDownLegs;
			}
			break;
		
		case kBeforeLayDownLegs:
			MoveDM();
		  MoveRM();
	//		if(TimeToLayDown())
			{
				LayDown();
				time_point_for_speed = kBeforeDMPosition;
			}
			break;
		
		case kBeforeDMPosition:
			MoveDM();
		  MoveRM();
		  if(DM_MoveInfo.motor_position&&RM_MoveInfo.motor_position)
			{
				time_point_for_speed = kBeforeLegTouchGround;
			}
			break;
			
		case kBeforeLegTouchGround:
		//	if(DetectLegLayDownPosition())
			{
				kLegState = ChangeLegState(kLegState);
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
	SetSpeedDirection();
	JudgeMovementSafiety();

	
	//DM运动部分详细参数计算
  RefreshMovementDataEveryBegining();
	CalMovementSpeed();
	CalMovementPosition(&DM_MoveInfo);
	
}

void RefreshMovementDataEveryBegining()
{
	DM_MoveInfo.distance_data.distance_all = DM_MoveInfo.distance_data.target_distance +
	CalRealDistance(fabs(DM_MoveInfo.position_data.initial_position - DriveMotor.PositionMeasure));	
	DM_MoveInfo.position_data.start_position = DriveMotor.PositionMeasure;
	DM_MoveInfo.distance_data.distance_left = 0;
	DM_MoveInfo.distance_data.distance_walked=0;
	DM_MoveInfo.position_data.position_left = 0;
	DM_MoveInfo.position_data.position_walked = 0;
}