#include "report_messages.h"
int message_id[4] = {30,31,32,20};
int messager_mark = 0;

void ReportMessage()
{
	ReportPositionXY();
	//ReportPositionY();
	//ReportState();
	//ReportCurve();
  //ReportPositionX();
	//ReportPositionY();
//	ReportClamberLegState();
	//ReportLegStateYaw();
	//ReportStepPosition();
}

void ReportCurve()
{
	VisualScope_Send(DriveMotor.PositionExpected,DriveMotor.PositionMeasure,DriveMotor.SpeedExpected,DriveMotor.SpeedMeasure);
}


void ReportPositionXY()
{
	COM_Frame SendFrame;
	SendFrame.Length = 16;
	SendFrame.Prop = message_id[messager_mark];	
	switch(messager_mark)
	{
		case 0:
	  SendFrame.Data.floats_ts[0] = location_data.laser_radar_position.ShouldBeTrusted;
	  SendFrame.Data.floats_ts[1] = location_data.relative_position.y;
	  SendFrame.Data.floats_ts[2] = location_data.current_position.lowleg_y;//relative_position_y;
	  SendFrame.Data.floats_ts[3] = location_data.current_position.highleg_y;
    messager_mark = 1;		
			break;
		
		case 1:
		SendFrame.Data.floats_ts[0] = kMachineAState;
	  SendFrame.Data.floats_ts[1] = kLegState;
	  SendFrame.Data.floats_ts[2] = time_point;
		SendFrame.Data.floats_ts[3] = DM_MoveInfo.distance_data.target_distance;
		messager_mark = 2;	
			break;
		
		case 2:
		SendFrame.Data.floats_ts[0] =  location_data.current_position.ground_leg_y;	
  	SendFrame.Data.floats_ts[1] =  location_data.current_position.suspend_leg_y;	
	  SendFrame.Data.floats_ts[2] = location_data.relative_data_y;
 		SendFrame.Data.floats_ts[3] = location_data.laser_radar_data_y;
		messager_mark = 3;	
			break;
		
		case 3:
		SendFrame.Data.floats_ts[0] = obstacle1.obstacle_exist;
    SendFrame.Data.floats_ts[1] = obstacle1.obstacle_location;
  	SendFrame.Data.floats_ts[2] = obstacle2.obstacle_exist;
  	SendFrame.Data.floats_ts[3] = obstacle2.obstacle_location;
		messager_mark = 0;	
			break;
		
		default:
			break;
	}
	FRAME_Send(&SendFrame,BLUETEETH_USART_MASK );
}


void ReportPositionY()
{
	COM_Frame SendFrame;
	SendFrame.Length = 16;
	SendFrame.Prop = message_id[messager_mark];	
	switch(messager_mark)
	{
		case 0:
	  SendFrame.Data.floats_ts[0] = location_data.laser1_data;
	  SendFrame.Data.floats_ts[1] = laser_radar_message[1];
	  SendFrame.Data.floats_ts[2] = location_data.current_position.lowleg_y;//relative_position_y;
	  SendFrame.Data.floats_ts[3] = location_data.current_position.highleg_y;
    messager_mark = 1;		
			break;
		
		case 1:
		SendFrame.Data.floats_ts[0] = kMachineAState;
	  SendFrame.Data.floats_ts[1] = kMachineAGeneralState;
	  SendFrame.Data.floats_ts[2] = time_point;
		SendFrame.Data.floats_ts[3] = DM_MoveInfo.distance_data.target_distance;
		messager_mark = 2;	
			break;
		
		case 2:
		SendFrame.Data.floats_ts[0] =  location_data.current_position.ground_leg_y;	
  	SendFrame.Data.floats_ts[1] =  location_data.laser_radar_data_y;	
	  SendFrame.Data.floats_ts[2] = DM_MoveInfo.motor_position;
 		SendFrame.Data.floats_ts[3] = RM_MoveInfo.motor_position;
		messager_mark = 3;	
			break;
		
		case 3:
		SendFrame.Data.floats_ts[0] = DM_speed_stage;
    SendFrame.Data.floats_ts[1] = RM_speed_stage;
  	SendFrame.Data.floats_ts[2] = GetTimeLeft();
  	SendFrame.Data.floats_ts[3] = kLegState;
		messager_mark = 0;	
			break;
		
		default:
			break;
	}
	FRAME_Send(&SendFrame,BLUETEETH_USART_MASK );
}

void ReportPositionX()
{
	COM_Frame SendFrame;
	SendFrame.Length = 64;
	SendFrame.Prop = 20;	
  SendFrame.Data.floats_ts[0] = location_data.current_position.highleg_x;
	SendFrame.Data.floats_ts[1] = location_data.current_position.lowleg_x;
	SendFrame.Data.floats_ts[2] = location_data.current_position.ground_leg_x;//relative_position_y;
	SendFrame.Data.floats_ts[3] = location_data.current_position.suspend_leg_x;		
	SendFrame.Data.floats_ts[4] = kMachineAState;
	SendFrame.Data.floats_ts[5] = time_point;
	SendFrame.Data.floats_ts[6] = leg_angle.lowleg_yaw;
	SendFrame.Data.floats_ts[7] = DriveMotor.PositionMeasure;	
	SendFrame.Data.floats_ts[8] =  DriveMotor.SpeedExpected;	
	SendFrame.Data.floats_ts[9] =  DriveMotor.PositionMeasure;	
	SendFrame.Data.floats_ts[10] = DriveMotor.PositionExpected;
  SendFrame.Data.floats_ts[11] = DriveMotor.State;//Pi*(decelerate_distance - distance_a)/2/(float)time_all/CalRealSpeed(speed_max);
	SendFrame.Data.floats_ts[12] = DM_speed_stage;
	SendFrame.Data.floats_ts[13] = RM_speed_stage;
	SendFrame.Data.floats_ts[14] = DM_MoveInfo.distance_data.target_distance;
	SendFrame.Data.floats_ts[15] = kLegState;
	FRAME_Send(&SendFrame,BLUETEETH_USART_MASK );
}

void ReportState()
{
	COM_Frame SendFrame;
	SendFrame.Length = 16;
	SendFrame.Prop = message_id[messager_mark];	
	switch(messager_mark)
	{
		case 0:
	  SendFrame.Data.floats_ts[0] = DM_MoveInfo.motor_position;
	  SendFrame.Data.floats_ts[1] = RM_MoveInfo.motor_position;
	  SendFrame.Data.floats_ts[2] = GetTimeLeft();//relative_position_y;
	  SendFrame.Data.floats_ts[3] = GetTimeLayDownAdvance();
    messager_mark = 1;		
			break;
		
		case 1:
		SendFrame.Data.floats_ts[0] = kMachineAState;
	  SendFrame.Data.floats_ts[1] = kMachineAGeneralState;
	  SendFrame.Data.floats_ts[2] = time_point;
		SendFrame.Data.floats_ts[3] = DriveMotor.SpeedMeasure;
		messager_mark = 2;	
			break;
		
		case 2:
		SendFrame.Data.floats_ts[0] =  DriveMotor.SpeedExpected;	
  	SendFrame.Data.floats_ts[1] =  DriveMotor.PositionMeasure;	
	  SendFrame.Data.floats_ts[2] = DriveMotor.PositionExpected;
 		SendFrame.Data.floats_ts[3] = DriveMotor.State;//Pi*(decele
		messager_mark = 3;	
			break;
		
		case 3:
		SendFrame.Data.floats_ts[0] = DM_speed_stage;
    SendFrame.Data.floats_ts[1] = RM_speed_stage;
  	SendFrame.Data.floats_ts[2] = DM_MoveInfo.speed_data.speed_direction;
  	SendFrame.Data.floats_ts[3] = kLegState;
		messager_mark = 0;	
			break;
		
		default:
			break;
	}
	FRAME_Send(&SendFrame,BLUETEETH_USART_MASK );
}

void ReportLegState()
{
				COM_Frame SendFrame;
	SendFrame.Length = 64;
	SendFrame.Prop = 20;	
  SendFrame.Data.floats_ts[0] = leg_data_feedback.leg_state_[0];
	SendFrame.Data.floats_ts[1] = leg_data_feedback.leg_state_[1];
	SendFrame.Data.floats_ts[2] = leg_data_feedback.leg_state_[2];//relative_position_y;
	SendFrame.Data.floats_ts[3] = leg_data_feedback.leg_state_[3];		
	SendFrame.Data.floats_ts[4] = leg_state_data.leglength_low.right_front;
	SendFrame.Data.floats_ts[5] = RotateMotor.PositionMeasure;
	SendFrame.Data.floats_ts[6] = leg_state_data.leg_state_number;
	SendFrame.Data.floats_ts[7] = leg_data_feedback.send_leg_change_flag;	
	SendFrame.Data.floats_ts[8] = leg_data_feedback.send_leg_height_change_flag;	
	SendFrame.Data.floats_ts[9] = kMachineAGeneralState;	
	SendFrame.Data.floats_ts[10] = time_point;
  SendFrame.Data.floats_ts[11] = RM_speed_stage;//Pi*(decelerate_distance - distance_a)/2/(float)time_all/CalRealSpeed(speed_max);
	SendFrame.Data.floats_ts[12] = RM_MoveInfo.motor_position;
	SendFrame.Data.floats_ts[13] = kMachineAState;
	SendFrame.Data.floats_ts[14] = leg_state_data.leglength_high.right_front;
	SendFrame.Data.floats_ts[15] = kLegState;
	FRAME_Send(&SendFrame,BLUETEETH_USART_MASK );
}

void ReportClamberLegState()
{
				COM_Frame SendFrame;
	SendFrame.Length = 64;
	SendFrame.Prop = 20;	
  SendFrame.Data.floats_ts[0] = leg_data_feedback.leg_state_[0];
	SendFrame.Data.floats_ts[1] = leg_data_feedback.leg_state_[1];
	SendFrame.Data.floats_ts[2] = leg_data_feedback.leg_state_[2];//relative_position_y;
	SendFrame.Data.floats_ts[3] = leg_data_feedback.leg_state_[3];		
	SendFrame.Data.floats_ts[4] = leg_state_data.leglength_low.right_front;
	SendFrame.Data.floats_ts[5] = leg_state_data.leglength_low.left_front;
	SendFrame.Data.floats_ts[6] = leg_state_data.leglength_low.left_behind;
	SendFrame.Data.floats_ts[7] = leg_state_data.leglength_low.right_behind;	
	SendFrame.Data.floats_ts[8] = leg_data_feedback.send_leg_height_change_flag;	
	SendFrame.Data.floats_ts[9] = leg_data_feedback.send_leg_change_flag;	
	SendFrame.Data.floats_ts[10] = leg_state_data.leg_state_number;
  SendFrame.Data.floats_ts[11] = DM_speed_stage;//Pi*(decelerate_distance - distance_a)/2/(float)time_all/CalRealSpeed(speed_max);
	SendFrame.Data.floats_ts[12] = time_point;
	SendFrame.Data.floats_ts[13] = kMachineAState;
	SendFrame.Data.floats_ts[14] = leg_state_data.leglength_high.right_front;
	SendFrame.Data.floats_ts[15] = kLegState;
	FRAME_Send(&SendFrame,BLUETEETH_USART_MASK );
}

void ReportLegStateYaw()
{
				COM_Frame SendFrame;
	SendFrame.Length = 64;
	SendFrame.Prop = 20;	
  SendFrame.Data.floats_ts[0] = leg_angle.highleg_yaw;
	SendFrame.Data.floats_ts[1] = leg_angle.lowleg_yaw;
	SendFrame.Data.floats_ts[2] = RotateMotor.PositionMeasure;//relative_position_y;
	SendFrame.Data.floats_ts[3] = leg_angle.original_yaw;		
	SendFrame.Data.floats_ts[4] = leg_angle.target_yaw;
	SendFrame.Data.floats_ts[5] = RM_MoveInfo.motor_position;
	SendFrame.Data.floats_ts[6] = RotateMotor.PositionMeasure;
	SendFrame.Data.floats_ts[7] = RotateMotor.PositionExpected;	
	SendFrame.Data.floats_ts[8] = RotateMotor.State;	
	SendFrame.Data.floats_ts[9] = time_point;	
	SendFrame.Data.floats_ts[10] = time_point;
  SendFrame.Data.floats_ts[11] = RM_speed_stage;//Pi*(decelerate_distance - distance_a)/2/(float)time_all/CalRealSpeed(speed_max);
	SendFrame.Data.floats_ts[12] = DM_speed_stage;
	SendFrame.Data.floats_ts[13] = kMachineAState;
	SendFrame.Data.floats_ts[14] = kMachineAGeneralState;
	SendFrame.Data.floats_ts[15] = kLegState;
	FRAME_Send(&SendFrame,BLUETEETH_USART_MASK );
}

void ReportStepPosition()
{
	COM_Frame SendFrame;
	SendFrame.Length = 64;
	SendFrame.Prop = 20;	
  SendFrame.Data.floats_ts[0] = leg_angle.highleg_yaw;
	SendFrame.Data.floats_ts[1] = leg_angle.lowleg_yaw;
	SendFrame.Data.floats_ts[2] = location_data.ground_leg_after_step;//relative_position_y;
	SendFrame.Data.floats_ts[3] = location_data.ground_leg_before_step;		
	SendFrame.Data.floats_ts[4] = location_data.suspend_leg_before_step;
	SendFrame.Data.floats_ts[5] = DM_MoveInfo.distance_data.target_distance;
	SendFrame.Data.floats_ts[6] = leg_data_feedback.crossed_step;
	SendFrame.Data.floats_ts[7] = leg_data_feedback.crossd_step_state;	
	SendFrame.Data.floats_ts[8] = RotateMotor.State;	
	SendFrame.Data.floats_ts[9] = 0;	
	SendFrame.Data.floats_ts[10] = time_point;
  SendFrame.Data.floats_ts[11] = RM_speed_stage;//Pi*(decelerate_distance - distance_a)/2/(float)time_all/CalRealSpeed(speed_max);
	SendFrame.Data.floats_ts[12] = DM_speed_stage;
	SendFrame.Data.floats_ts[13] = kMachineAState;
	SendFrame.Data.floats_ts[14] = kMachineAGeneralState;
	SendFrame.Data.floats_ts[15] = kLegState;
	FRAME_Send(&SendFrame,BLUETEETH_USART_MASK );
}