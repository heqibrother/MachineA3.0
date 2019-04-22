#include "report_messages.h"

void ReportMessage()
{
   ReportPosition();
}

void ReportCurve()
{
	VisualScope_Send(DriveMotor.PositionExpected,DriveMotor.PositionMeasure,DriveMotor.SpeedExpected,DriveMotor.SpeedMeasure);
}

void ReportPosition()
{
			COM_Frame SendFrame;
	SendFrame.Length = 64;
	SendFrame.Prop = 20;	
  SendFrame.Data.floats_ts[0] = location_data.current_position.highleg_y;
	SendFrame.Data.floats_ts[1] = location_data.current_position.lowleg_y;
	SendFrame.Data.floats_ts[2] = location_data.current_position.ground_leg_y;//relative_position_y;
	SendFrame.Data.floats_ts[3] = location_data.current_position.suspend_leg_y;		
	SendFrame.Data.floats_ts[4] = kMachineAState;
	SendFrame.Data.floats_ts[5] = leg_data_feedback.leg_state_[0];
	SendFrame.Data.floats_ts[6] = leg_state_data.leg_state_number;
	SendFrame.Data.floats_ts[7] = leg_state_data.leg_state_number_pre;	
	SendFrame.Data.floats_ts[8] =  leg_data_feedback.leg_state_feedback;	
	SendFrame.Data.floats_ts[9] =  time_point_for_location;	
	SendFrame.Data.floats_ts[10] = time_point_for_speed;
  SendFrame.Data.floats_ts[11] = RM_speed_stage;//Pi*(decelerate_distance - distance_a)/2/(float)time_all/CalRealSpeed(speed_max);
	SendFrame.Data.floats_ts[12] = DM_speed_stage;
	SendFrame.Data.floats_ts[13] = movement_style;
	SendFrame.Data.floats_ts[14] = kMachineAGeneralState;
	SendFrame.Data.floats_ts[15] = kLegState;
	FRAME_Send(&SendFrame,BLUETEETH_USART_MASK );
}

void ReportState()
{
			COM_Frame SendFrame;
	SendFrame.Length = 64;
	SendFrame.Prop = 20;	
  SendFrame.Data.floats_ts[0] = DM_MoveInfo.motor_position;
	SendFrame.Data.floats_ts[1] = RM_MoveInfo.motor_position;
	SendFrame.Data.floats_ts[2] = GetTimeLeft();//relative_position_y;
	SendFrame.Data.floats_ts[3] = GetTimeLayDownAdvance();		
	SendFrame.Data.floats_ts[4] = time_point_for_speed;
	SendFrame.Data.floats_ts[5] = leg_data_feedback.leg_state_[2];
	SendFrame.Data.floats_ts[6] = leg_data_feedback.leg_state_[1];
	SendFrame.Data.floats_ts[7] = leg_data_feedback.leg_state_[0];	
	SendFrame.Data.floats_ts[8] = kMachineAGeneralState;	
	SendFrame.Data.floats_ts[9] = kMachineAState;	
	SendFrame.Data.floats_ts[10] = MyGetTime();
  SendFrame.Data.floats_ts[11] = RM_speed_stage;//Pi*(decelerate_distance - distance_a)/2/(float)time_all/CalRealSpeed(speed_max);
	SendFrame.Data.floats_ts[12] = DM_speed_stage;
	SendFrame.Data.floats_ts[13] = movement_style;
	SendFrame.Data.floats_ts[14] = DM_MoveInfo.speed_data.speed_direction;
	SendFrame.Data.floats_ts[15] = kLegState;
	FRAME_Send(&SendFrame,BLUETEETH_USART_MASK );
}