/*
   Constructing the Fundamental Function of Direct Motor Motion
*/

#include "DM_motor_movement.h"

SpeedStage DM_speed_stage;
void MoveDM()
{
	JudgeDMSpeedStage();
	switch(DM_speed_stage)
	{
		case kStopMove:
			DMStopMove();
			break;
		
		case kAccelerate:
			DMAccelerate();
			break;
		
		case kKeepSpeed:
			DMKeepSpeed();
			break;
		
		case kDeccelerate:
			DMDeccelerate();
			break;
		
		default:
			break;
	}
}

void JudgeDMSpeedStage()
{

	if(JugdeStageTool(DriveMotor.PositionMeasure,DM_MoveInfo.position_data.finish_decelerate_position))
	{
		DM_MoveInfo.motor_position = true;
	}
	else if(JugdeStageTool(DriveMotor.PositionMeasure,DM_MoveInfo.position_data.finish_keepspeed_position))
	{
		DM_speed_stage = kDeccelerate;
	}
	else if(JugdeStageTool(DriveMotor.PositionMeasure,DM_MoveInfo.position_data.finish_accelerate_position))
	{
		DM_speed_stage = kKeepSpeed;
	}
	else
	{
		DM_speed_stage = kAccelerate;
	}	
	
	if(DM_MoveInfo.motor_position&&DM_speed_stage!=kStopMove)
	{
		DM_speed_stage = kStopMove;
	}
}

void DMStopMove()
{
	if(DriveMotor.State!=PIDPOSITION)
	{
		DriveMotor.State=PIDPOSITION;
		DriveMotor.PositionExpected = DriveMotor.PositionMeasure;
	}
}

void DMAccelerate()
{
	DriveMotor.State=PIDSPEED;
	DM_MoveInfo.speed_data.current_expected_speed = SuitableAccelerateSpeed();
	DriveMotor.SpeedExpected = DM_MoveInfo.speed_data.speed_direction * DM_MoveInfo.speed_data.current_expected_speed;
}

void DMKeepSpeed()
{
	DriveMotor.State=PIDSPEED;
	DM_MoveInfo.speed_data.current_expected_speed = DM_MoveInfo.speed_data.target_position_speed;
	DriveMotor.SpeedExpected = DM_MoveInfo.speed_data.speed_direction * DM_MoveInfo.speed_data.current_expected_speed;
}

void DMDeccelerate()
{
	DriveMotor.State=PIDSPEED;
	DM_MoveInfo.speed_data.current_expected_speed = SuitableDecelerateSpeed();
	DriveMotor.SpeedExpected = DM_MoveInfo.speed_data.speed_direction * DM_MoveInfo.speed_data.current_expected_speed;
}

float SuitableAccelerateSpeed()
{
	float result = 0;
	int32_t time_walked = 0;
	time_walked = LookUpDMTimeTable(DM_MoveInfo.distance_data.distance_walked/DM_MoveInfo.distance_data.distance_accelerate)*DM_MoveInfo.time_data.accelerate_time;
	result = DM_MoveInfo.speed_data.target_position_speed * LookUpDMSpeedTable((float)time_walked/DM_MoveInfo.time_data.accelerate_time);
	return result;
}

float SuitableDecelerateSpeed()
{
	float result = 0;
	int32_t time_left = 0;
	time_left = LookUpDMTimeTable(DM_MoveInfo.distance_data.distance_left/DM_MoveInfo.distance_data.distance_decelerate)*DM_MoveInfo.time_data.decelerate_time;
	result = DM_MoveInfo.speed_data.target_position_speed * LookUpDMSpeedTable((float)time_left/DM_MoveInfo.time_data.decelerate_time);
	return result;
}

bool JugdeStageTool(float value_a,float value_b)
{
	if(value_a*DM_MoveInfo.speed_data.speed_direction > value_b*DM_MoveInfo.speed_data.speed_direction)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void DMPartInit()
{
	DM_MoveInfo.distance_data.target_distance = 0;
	DM_MoveInfo.speed_data.target_position_speed = 0;
	SetSpeedDirection();
	DM_MoveInfo.position_data.initial_position =  + 12.5 / DM_radio ;
	DM_speed_stage = kStopMove;
	DM_MoveInfo.motor_position = true;
}

void SetSpeedDirection()
{
	if(kLegState == kHighLegMove)
	{
		DM_MoveInfo.speed_data.speed_direction = -1.0f;
	}
	else if(kLegState == kLowLegMove)
	{
		DM_MoveInfo.speed_data.speed_direction = 1.0f;
	}
}