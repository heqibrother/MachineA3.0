/*
   To determine the timing of different motion control 
	 modes, it is mainly divided into speed-first and 
	 location-first timing control.
*/

#include "movement.h"

MotorMoveState DM_MoveInfo,RM_MoveInfo;
MovementStyle movement_style;
TimePoint time_point;
Obstacle obstacle1,obstacle2;

bool ExecutePlan()
{
	switch(movement_style)
	{
		case kSpeedFirst:
			SpeedFirstMode();
		  if(time_point == kAllDone)
			{
				return true;
			}
			break;
		
		case kLocationFirst:
			LocationFirstMode();
			if(time_point == kAllDone)
			{
				return true;
			}
			break;
			
		case kClamberPrepare:
			ClamberPrepareMode();
			if(time_point == kAllDone)
			{
				return true;
			}
			break;
			
		case kClamberWorking:
			ClamberWorkingMode();
			if(time_point == kAllDone)
			{
				return true;
			}
			break;
		
		default:
			break;
	}
	return false;
}

void ClamberWorkingMode()
{
	switch(time_point)
	{
		case kBeforeFurtherPlan:
			CalculateClamberMovementData();
		  time_point = kBeforeRecoverLeg;
			//break;
		
		case kBeforeRecoverLeg:
			MoveDM();
		  if(DetectLegRecoverPosition())
			{
				 MoveRM();
				time_point = kBeforeRiseItself;
				//LegModeChange();//在这一阶段执行，避免反复置位
			}
			else break;
		
		case kBeforeRiseItself:
			MoveDM();
		  MoveRM();
		  if(LegPartAnswer())
			{
				time_point = kBeforeSelfCorrection;
				//LegModeChange();//在这一阶段执行，避免反复置位
			}
			else break;
			
			case kBeforeSelfCorrection:
			MoveDM();
		  MoveRM();
		  if(LegPartAnswer()&&LegCrossOtherLeg())
			{
				time_point = kBeforeLayDownLegs;
				LegModeChange();//在这一阶段执行，避免反复置位
				SendLegLength();
			}
			else break;
			
		case kBeforeLayDownLegs:
			MoveDM();
		  MoveRM();
			if(TimeToLayDown())
			{
				LayDown();
				time_point = kBeforeDMPosition;
			}
			else break;
		
		case kBeforeDMPosition:
			MoveDM();
		  MoveRM();
		  if(DM_MoveInfo.motor_position&&RM_MoveInfo.motor_position)
			{
				time_point = kBeforeLegTouchGround;
			}
			else break;
			
		case kBeforeLegTouchGround:
				kLegState = ChangeLegState(kLegState);
			   SetSpeedDirection();
				time_point = kAllDone;
		
		case kAllDone:
				obstacle1.obstacle_exist = false;
		    obstacle2.obstacle_exist = false;
			break;
		
		default:
			break;
	}
}

void ClamberPrepareMode()
{
	switch(time_point)
	{
		case kBeforeFurtherPlan:
			CalMovementDataForClamberMode();
		  time_point = kBeforeRecoverLeg;
			//break;
		
		case kBeforeRecoverLeg:
			FlexibleMoveDM();
		  if(DetectLegRecoverPosition())
			{
				 MoveRM();
				time_point = kBeforeRiseItself;
				LegModeChange();//在这一阶段执行，避免反复置位
			}
			else break;
		
		case kBeforeRiseItself:
			FlexibleMoveDM();
		  MoveRM();
		  if(LegPartAnswer())
			{
				time_point = kBeforeDMPosition;
			}
			else break;
		
		case kBeforeDMPosition:
			FlexibleMoveDM();
		  MoveRM();
		  if(DM_MoveInfo.motor_position&&RM_MoveInfo.motor_position
				&&(DetectLegAllPosition()))//确保腿已经缩到位
			{
				time_point = kBeforeLegTouchGround;
				HighlegLift();
				kLegState = kLowLegMove;//因为实际腿状态切换为高腿在上，所以只有把状态切换为矮腿，才能执行下面的是否到位判断
			}
			else break;
			
		case kBeforeLegTouchGround:
				if(LegPartAnswer()&&DetectLegLayDownPosition())//确保腿站稳
				{ 
					kLegState = kHighLegMove;
					SetSpeedDirection();
					time_point = kAllDone;
				}
				else break;
		
		case kAllDone:
				obstacle1.obstacle_exist = false;
		    obstacle2.obstacle_exist = false;
			break;
		
		default:
			break;
	}
}

void SpeedFirstMode()
{
	switch(time_point)
	{
		case kBeforeFurtherPlan:
			CalculateFurtherMovementData();
		  time_point = kBeforeRecoverLeg;
			//break;
		
		case kBeforeRecoverLeg:
			MoveDM();
		  if(DetectLegRecoverPosition())
			{
				MoveRM();
				time_point = kBeforeRiseItself;
				LegModeChange();//在这一阶段执行，避免反复置位
			}
			else break;
		
		case kBeforeRiseItself:
			MoveDM();
		  MoveRM();
		  if(LegPartAnswer())
			{
				time_point = kBeforeLayDownLegs;
			}
			else break;
		
		case kBeforeLayDownLegs:
			MoveDM();
		  MoveRM();
			if(TimeToLayDown())
			{
				LayDown();
				time_point = kBeforeDMPosition;
			}
			else break;
		
		case kBeforeDMPosition:
			MoveDM();
		  MoveRM();
		  if(DM_MoveInfo.motor_position&&RM_MoveInfo.motor_position)
			{
				time_point = kBeforeLegTouchGround;
			}
			else break;
			
		case kBeforeLegTouchGround:
				kLegState = ChangeLegState(kLegState);
			   SetSpeedDirection();
				time_point = kAllDone;
		
		case kAllDone:
				obstacle1.obstacle_exist = false;
		    obstacle2.obstacle_exist = false;
			break;
		
		default:
			break;
	}
}
		
void LocationFirstMode()
{
	switch(time_point)
	{
		case kBeforeFurtherPlan:
			CalculateFurtherMovementData();
		  time_point = kBeforeRecoverLeg;
			//break;
		
		case kBeforeRecoverLeg:
		  if(SafeToMoveBeforeRecover())
			{
				MoveDM();
			}
			if(DetectLegRecoverPosition())
			{
				MoveDM();
				MoveRM();
				time_point = kBeforeRiseItself;
				LegModeChange();//在这一阶段执行，避免反复置位
			}
			else break;
		
		case kBeforeRiseItself:
				MoveDM();
		    MoveRM(); 
		  if(LegPartAnswer()&&LegCrossOtherLeg())
			{
				time_point = kBeforeSelfCorrection;
			}
			else break;
			
		case kBeforeSelfCorrection:
			SelfCorrection();
			time_point = kBeforeLayDownLegs;
			//break;
			
		case kBeforeLayDownLegs:
			MoveDM();
		  MoveRM();
			if(SafeToLayDownBeforePosition()&&TimeToLayDown())
			{
				LayDown();
				time_point = kBeforeDMPosition;
			}
			else break;
		
		case kBeforeDMPosition:
			MoveDM();
		  MoveRM();
		  if(DM_MoveInfo.motor_position&&RM_MoveInfo.motor_position)
			{
				time_point = kBeforeLegTouchGround;
			}
			else break;
			
		case kBeforeLegTouchGround:
			if(DetectLegLayDownPosition())
			{
				kLegState = ChangeLegState(kLegState);
					SetSpeedDirection();
				time_point = kAllDone;
			}
			else break;
		
		case kAllDone:
				obstacle1.obstacle_exist = false;
		    obstacle2.obstacle_exist = false;
			break;
		
		default:
			break;
	}
}


void CalculateClamberMovementData()
{
		SetSpeedDirection();
	JudgeMovementSafiety();

	RM_MoveInfo.position_data.finish_decelerate_position = RotateMotor.PositionMeasure + RM_MoveInfo.speed_data.speed_direction 
	                                                        * (leg_angle.target_yaw - leg_angle.suspendleg_yaw) / RM_radio;
	DM_MoveInfo.position_data.start_position = DriveMotor.PositionMeasure;
	//DM运动部分详细参数计算
  RefreshMovementDataEveryBegining();
	CalMovementSpeed(600);
	CalMovementPosition(&DM_MoveInfo);
	if(2*DM_MoveInfo.speed_data.target_position_speed<400)
	{
		RM_speed_limit = (int)(2.0f*DM_MoveInfo.speed_data.target_position_speed);
	}
	else
	{
		RM_speed_limit = 400;
	}
}
void CalculateFurtherMovementData()
{	
	SetSpeedDirection();
	JudgeMovementSafiety();

	RM_MoveInfo.position_data.finish_decelerate_position = RotateMotor.PositionMeasure + RM_MoveInfo.speed_data.speed_direction 
	                                                        * (leg_angle.target_yaw - leg_angle.suspendleg_yaw) / RM_radio;
	DM_MoveInfo.position_data.start_position = DriveMotor.PositionMeasure;
	//DM运动部分详细参数计算
  RefreshMovementDataEveryBegining();
	CalMovementSpeed(400);
	CalMovementPosition(&DM_MoveInfo);
	if(2*DM_MoveInfo.speed_data.target_position_speed<400)
	{
		RM_speed_limit = (int)(2.0f*DM_MoveInfo.speed_data.target_position_speed);
	}
	else
	{
		RM_speed_limit = 400;
	}
}

void CalMovementDataForClamberMode()
{	
	SetSpeedDirection();
	RM_MoveInfo.position_data.finish_decelerate_position = RM_MoveInfo.position_data.initial_position;
	//DM运动部分详细参数计算
  RefreshMovementDataEveryBegining();
	CalMovementSpeed(400);
	CalMovementPosition(&DM_MoveInfo);
	if(2*DM_MoveInfo.speed_data.target_position_speed<400)
	{
		RM_speed_limit = (int)(2.0f*DM_MoveInfo.speed_data.target_position_speed)*DM_MoveInfo.speed_data.speed_direction;
	}
	else
	{
		RM_speed_limit = 400;
	}
}

bool SafeToMoveBeforeRecover()
{
	if((obstacle1.obstacle_location>150||!obstacle1.obstacle_exist)
		&&(obstacle2.obstacle_location>150||!obstacle2.obstacle_exist))return true;
  return false;
}

bool SafeToLayDownBeforePosition()
{
	if(DM_MoveInfo.motor_position)return true;
//	if((2*(DM_MoveInfo.distance_data.distance_all - DM_MoveInfo.distance_data.distance_left)>obstacle1.obstacle_location||!obstacle1.obstacle_exist)
//		&&(2*(DM_MoveInfo.distance_data.distance_all - DM_MoveInfo.distance_data.distance_left)>obstacle2.obstacle_location||!obstacle2.obstacle_exist))return true;
	return false;
}

void RefreshMovementDataEveryBegining()
{
	DM_MoveInfo.distance_data.distance_all = DM_MoveInfo.distance_data.target_distance +
	CalRealDistance(DM_MoveInfo.speed_data.speed_direction*(DM_MoveInfo.position_data.initial_position - DriveMotor.PositionMeasure));	
	DM_MoveInfo.position_data.start_position = DriveMotor.PositionMeasure;
	DM_MoveInfo.distance_data.distance_left = 0;
	DM_MoveInfo.distance_data.distance_walked=0;
	DM_MoveInfo.position_data.position_left = 0;
	DM_MoveInfo.position_data.position_walked = 0;
}

void SelfCorrection()
{
	
}

void SetObstacleLocation(float obstacleposition,float obstaclewidth,Obstacle *targetobstacle)
{
	(*targetobstacle).obstacle_location = obstacleposition;
	(*targetobstacle).obstacle_width = obstaclewidth;
	(*targetobstacle).obstacle_exist = true;
}

void RefreshMovementData()
{
	RefreshLegYaw();
}

bool LegCrossOtherLeg()
{
	if((DriveMotor.PositionMeasure-DM_MoveInfo.position_data.initial_position)*DM_radio*DM_MoveInfo.speed_data.speed_direction > 0)//Aluminum_Tube_Width/2)
	{
		return true;
	}
	return false;
}