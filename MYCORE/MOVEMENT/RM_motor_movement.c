/**
 * @brief: Constructing the Fundamental Function of Rotating Motor Motion
 * @status: 2019.4.14
 */
#include "RM_motor_movement.h"

SpeedStage RM_speed_stage;

void MoveRM()
{
	JudgeRMSpeedStage();
	switch(RM_speed_stage)
	{
		case kStopMove:
			RMStopMove();
			break;
		
	  case kAccelerate:
			RMAccelerate();
			break;
		
		case kDeccelerate:
			RMDecelerate();
			break;
		
		default:
			break;
	}
}

void JudgeRMSpeedStage()
{
  if(!RM_MoveInfo.motor_position&&RM_speed_stage==kStopMove)
	{
		RM_speed_stage = kAccelerate;
	}
	else if(RM_speed_stage==kAccelerate)
	{
		RM_speed_stage = kDeccelerate;
	}
	
	if(RM_MoveInfo.motor_position&&RM_speed_stage!=kStopMove)
	{
		RM_speed_stage = kStopMove;
	}
}

void RMStopMove()
{
	securityitem.sMotorState.refresh_flag = true;
		RotateMotor.State = PIDPOSITION;
		RotateMotor.PositionExpected = RM_MoveInfo.position_data.finish_decelerate_position;
}

void RMAccelerate()
{
	securityitem.sMotorState.refresh_flag = true;
	RotateMotor.State = PIDPOSITION;
	RotateMotor.PositionExpected = RM_MoveInfo.position_data.finish_decelerate_position;
}

void RMDecelerate()
{
	if(fabs(RM_MoveInfo.position_data.finish_decelerate_position - RotateMotor.PositionMeasure)<5)
	{
		RM_MoveInfo.motor_position = true;
		RM_speed_stage = kStopMove;
	}
	
}

void RMPartInit()
{
	RM_speed_stage = kStopMove;
	RM_MoveInfo.position_data.initial_position = 0;
	RM_MoveInfo.position_data.finish_decelerate_position = 0;
}