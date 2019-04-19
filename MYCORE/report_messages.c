#include "report_messages.h"

void ReportMessage()
{
		COM_Frame SendFrame;
	SendFrame.Length = 64;
	SendFrame.Prop = 20;	
  SendFrame.Data.floats_ts[0] = DM_MoveInfo.motor_position;
	SendFrame.Data.floats_ts[1] = DM_MoveInfo.speed_data.target_position_speed;
	SendFrame.Data.floats_ts[2] = DM_MoveInfo.speed_data.current_expected_speed;//relative_position_y;
	SendFrame.Data.floats_ts[3] = DM_MoveInfo.distance_data.distance_all ;		
	SendFrame.Data.floats_ts[4] = DM_MoveInfo.distance_data.distance_accelerate;
	SendFrame.Data.floats_ts[5] = DM_MoveInfo.distance_data.distance_decelerate;
	SendFrame.Data.floats_ts[6] = DM_MoveInfo.time_data.accelerate_time;
	SendFrame.Data.floats_ts[7] = DM_MoveInfo.time_data.decelerate_time;	
	SendFrame.Data.floats_ts[8] = DM_MoveInfo.position_data.finish_accelerate_position;	
	SendFrame.Data.floats_ts[9] = DM_MoveInfo.position_data.finish_decelerate_position;	
	SendFrame.Data.floats_ts[10] = MyGetTime();
  SendFrame.Data.floats_ts[11] = RM_speed_stage;//Pi*(decelerate_distance - distance_a)/2/(float)time_all/CalRealSpeed(speed_max);
	SendFrame.Data.floats_ts[12] = DM_speed_stage;
	SendFrame.Data.floats_ts[13] = movement_style;
	SendFrame.Data.floats_ts[14] = DM_MoveInfo.speed_data.speed_direction;
	SendFrame.Data.floats_ts[15] = kLegState;
	FRAME_Send(&SendFrame,BLUETEETH_USART_MASK );
}
