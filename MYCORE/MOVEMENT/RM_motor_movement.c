/**
 * @brief: Constructing the Fundamental Function of Rotating Motor Motion
 * @status: 2019.4.14
 */
#include "RM_motor_movement.h"
const float RM_radio = 0.32075;//34:106 //   360/80pi£¨3.141592654£© //motor_angle * radio = real angle
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
  if(fabs(RotateMotor.PositionExpected - RotateMotor.PositionMeasure)>5)
	{
		RotateMotor.State = PIDPOSITION;
		RotateMotor.PositionExpected = RotateMotor.PositionMeasure;
	}
}

void RMAccelerate()
{
	RotateMotor.State = PIDPOSITION;
	RotateMotor.State = RM_MoveInfo.position_data.finish_decelerate_position;
}

void RMDecelerate()
{
	if(fabs(RM_MoveInfo.position_data.finish_decelerate_position - RotateMotor.PositionMeasure)<5)
	{
		RM_MoveInfo.motor_position = true;
	}
	
}

void RMPartInit()
{
	RM_speed_stage = kStopMove;
	RM_MoveInfo.position_data.finish_decelerate_position = 0;
}