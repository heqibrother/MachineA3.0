/*
   Constructing the Fundamental Function of Direct Motor Motion
*/

#include "DM_motor_movement.h"

SpeedStage DM_speed_stage;
void MoveDM()
{
	JudgeDMSpeedStage();
	if(DM_speed_stage!=kStopMove)RefreshMotorDistanceWalked();
	else{//防止电机到位，但position_left没清零（判断间隔）
			DM_MoveInfo.distance_data.distance_left = 0;
	DM_MoveInfo.position_data.position_left = 0;
	}
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
		DMStopMove();
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
	//securityitem.sMotorState.refresh_flag = true;
	if(DriveMotor.State!=PIDPOSITION)
	{
		DriveMotor.State=PIDPOSITION;
		DriveMotor.PositionExpected = DriveMotor.PositionMeasure;
	}
	DM_MoveInfo.position_data.record_position = DriveMotor.PositionMeasure;
}

void DMAccelerate()
{
	//securityitem.sMotorState.refresh_flag = true;
	DriveMotor.State=PIDSPEED;
	DM_MoveInfo.speed_data.current_expected_speed = SuitableAccelerateSpeed();
	DriveMotor.SpeedExpected = (int16_t)(DM_MoveInfo.speed_data.speed_direction * DM_MoveInfo.speed_data.current_expected_speed);
}

void DMKeepSpeed()
{
	//securityitem.sMotorState.refresh_flag = true;
	DriveMotor.State=PIDSPEED;
	DM_MoveInfo.speed_data.current_expected_speed = DM_MoveInfo.speed_data.target_position_speed;
	DriveMotor.SpeedExpected = (int16_t)(DM_MoveInfo.speed_data.speed_direction * DM_MoveInfo.speed_data.current_expected_speed);
}

void DMDeccelerate()
{
	//securityitem.sMotorState.refresh_flag = true;
	DriveMotor.State=PIDSPEED;
	DM_MoveInfo.speed_data.current_expected_speed = SuitableDecelerateSpeed();
	DriveMotor.SpeedExpected = (int16_t)(DM_MoveInfo.speed_data.speed_direction * DM_MoveInfo.speed_data.current_expected_speed);
}

float SuitableAccelerateSpeed()
{
	float result = 0;
	int32_t time_walked = 0;
	time_walked = LookUpDMTimeTable(DM_MoveInfo.distance_data.distance_walked/DM_MoveInfo.distance_data.distance_accelerate)*DM_MoveInfo.time_data.accelerate_time;
	if(DM_MoveInfo.time_data.accelerate_time!=0)
	result = DM_MoveInfo.speed_data.target_position_speed * LookUpDMSpeedTable((float)time_walked/(float)Int32_tSafeDivision(DM_MoveInfo.time_data.accelerate_time));
	
		if(fabs(result)<fabs(DM_MoveInfo.speed_data.target_position_speed/20.0f))
	return DM_MoveInfo.speed_data.target_position_speed/20.0f;
	return result;
}

float SuitableDecelerateSpeed()
{
	float result = 0;
	int32_t time_left = 0;
	time_left = LookUpDMTimeTable(DM_MoveInfo.distance_data.distance_left/DM_MoveInfo.distance_data.distance_decelerate)*DM_MoveInfo.time_data.decelerate_time;
	if(DM_MoveInfo.time_data.decelerate_time!=0)
	result = DM_MoveInfo.speed_data.target_position_speed * LookUpDMSpeedTable((float)time_left/(float)Int32_tSafeDivision(DM_MoveInfo.time_data.decelerate_time));
		if(fabs(result)<fabs(DM_MoveInfo.speed_data.target_position_speed/20.0f))
	return DM_MoveInfo.speed_data.target_position_speed/20.0f;
	return result;
}

bool JugdeStageTool(float value_a,float value_b)
{
	if(value_a*DM_MoveInfo.speed_data.speed_direction*DM_MoveInfo.move_direction > value_b*DM_MoveInfo.speed_data.speed_direction*DM_MoveInfo.move_direction)
	{
		return true;
	}
	else
	{
		return false;
	}
}
int32_t GetTimeLeft()
{
	int32_t result;
	if(DM_MoveInfo.distance_data.distance_left<DM_MoveInfo.distance_data.distance_decelerate)
	{//减速区
		result = (int32_t)(LookUpDMTimeTable(DM_MoveInfo.distance_data.distance_left/FloatSafeDivision(DM_MoveInfo.distance_data.distance_decelerate))*DM_MoveInfo.time_data.decelerate_time);
	}
	else if(DM_MoveInfo.distance_data.distance_walked>DM_MoveInfo.distance_data.distance_accelerate)
	{
		result = (int32_t)((DM_MoveInfo.distance_data.distance_all-DM_MoveInfo.distance_data.distance_decelerate - DM_MoveInfo.distance_data.distance_walked)
		          /FloatSafeDivision(CalRealSpeed(DM_MoveInfo.speed_data.target_position_speed)));
		result = result + DM_MoveInfo.time_data.decelerate_time;
	}
	else
	{
		result = (int32_t)((1.0f-LookUpDMTimeTable(DM_MoveInfo.distance_data.distance_walked/FloatSafeDivision(DM_MoveInfo.distance_data.distance_accelerate)))*DM_MoveInfo.time_data.accelerate_time);
		result = result + DM_MoveInfo.time_data.keepspeed_time + DM_MoveInfo.time_data.decelerate_time;
	}
	return result;
}

void DMPartInit()
{
	DM_MoveInfo.distance_data.target_distance = 0;
	DM_MoveInfo.speed_data.target_position_speed = 0;
	SetSpeedDirection();
	DM_MoveInfo.position_data.initial_position =  field_direction * 12.5f / FloatSafeDivision(DM_radio) ;
	DM_speed_stage = kStopMove;
	DM_MoveInfo.motor_position = true;
	obstacle1.obstacle_exist = false;
	obstacle2.obstacle_exist = false;
}

void SetSpeedDirection()
{
	if(kLegState == kHighLegMove)
	{
		DM_MoveInfo.speed_data.speed_direction = -1.0f ;
		RM_MoveInfo.speed_data.speed_direction = -1.0f ;
	}
	else if(kLegState == kLowLegMove)
	{
		DM_MoveInfo.speed_data.speed_direction = 1.0f;
		RM_MoveInfo.speed_data.speed_direction = 1.0f;
	}
	DM_MoveInfo.move_direction  = 1.0f;
}

void RefreshMotorDistanceWalked()
{
	DM_MoveInfo.position_data.position_walked = DM_MoveInfo.position_data.position_walked + fabs(DriveMotor.PositionMeasure - DM_MoveInfo.position_data.record_position);
	DM_MoveInfo.position_data.record_position = DriveMotor.PositionMeasure;
	DM_MoveInfo.distance_data.distance_walked = CalRealDistance(DM_MoveInfo.position_data.position_walked);
	
	DM_MoveInfo.position_data.position_left = DM_MoveInfo.speed_data.speed_direction*(DM_MoveInfo.position_data.finish_decelerate_position - DriveMotor.PositionMeasure);
	if(DM_MoveInfo.position_data.position_left<0)DM_MoveInfo.position_data.position_left = 0;
	DM_MoveInfo.distance_data.distance_left = CalRealDistance(DM_MoveInfo.position_data.position_left);
}

void FlexibleMoveDM()
{
	if(fabs(DM_MoveInfo.position_data.finish_decelerate_position - DM_MoveInfo.position_data.start_position)>50)
	{
		MoveDM();
	}
	else
	{
		securityitem.sMotorState.refresh_flag = true;
		DriveMotor.State = PIDPOSITION;
		DriveMotor.PositionExpected = DM_MoveInfo.position_data.finish_decelerate_position;
		if(fabs(DriveMotor.PositionMeasure-DriveMotor.PositionExpected)<5)
		{
			DM_MoveInfo.motor_position = true;
		}
	}
}