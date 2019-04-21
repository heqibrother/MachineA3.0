/*
   Responsible for overall locationing
*/
#include "location.h"
LocationData location_data;
int16_t laser_radar_message[4] = {0};

void RefreshLocation()
{
	RefreshCurrentPosition();
}

void RecordLocation()
{
	if(kLegState == kHighLegMove)
	{
		location_data.current_position.ground_leg_x = location_data.current_position.lowleg_x;
		location_data.current_position.ground_leg_y = location_data.current_position.lowleg_y;
		location_data.current_position.suspend_leg_x = location_data.current_position.highleg_x;
		location_data.current_position.suspend_leg_y = location_data.current_position.highleg_y;
		location_data.motor_position.ground_leg_x = location_data.motor_position.lowleg_x;
		location_data.motor_position.ground_leg_y = location_data.motor_position.lowleg_y;
		location_data.motor_position.suspend_leg_x = location_data.motor_position.highleg_x;
		location_data.motor_position.suspend_leg_y = location_data.motor_position.highleg_y;
	}
	else if(kLegState == kLowLegMove)
	{
		location_data.current_position.ground_leg_x = location_data.current_position.highleg_x;
		location_data.current_position.ground_leg_y = location_data.current_position.highleg_y;
		location_data.current_position.suspend_leg_x = location_data.current_position.lowleg_x;
		location_data.current_position.suspend_leg_y = location_data.current_position.lowleg_y;
		location_data.motor_position.ground_leg_x = location_data.motor_position.highleg_x;
		location_data.motor_position.ground_leg_y = location_data.motor_position.highleg_y;
		location_data.motor_position.suspend_leg_x = location_data.motor_position.lowleg_x;
		location_data.motor_position.suspend_leg_y = location_data.motor_position.lowleg_y;
	}
}

void SendLocationInfo()
{
	laser_radar_message[0] =  -1*field_direction*(Column_Position_X - location_data.motor_position.highleg_x);;
	laser_radar_message[1] = Hill_Position_Y - CalOpositionY(Rplidar_position_X,Rplidar_position_Y,kHighLegMove) - location_data.motor_position.highleg_y;
	laser_radar_message[2] = leg_angle.highleg_yaw;
   SendPCMessage(laser_radar_message[0],laser_radar_message[1],laser_radar_message[2],field_direction
	              ,kMachineAGeneralState,kMachineAState,kLegState,location_data.current_position.highleg_y,location_data.current_position.lowleg_y);
}

void SendPCMessage(short I1, short I2,short I3,short I4,short I5, short I6,short I7,short I8)
{
	CanTxMsg TxMessage;
	uint16_t i = 0;
	uint8_t TransmitMailbox = CAN_TxStatus_NoMailBox;	
	uint16_t  time_out_count = 0;
	TxMessage.StdId=0x140;
	TxMessage.IDE=CAN_ID_STD;
	TxMessage.RTR=CAN_RTR_DATA;
	TxMessage.DLC=8;
	
	TxMessage.Data[0]=I1>>8;
	TxMessage.Data[1]=I1&0xff;
	TxMessage.Data[2]=I2>>8;
	TxMessage.Data[3]=I2&0xff;
	TxMessage.Data[4]=I3>>8;
	TxMessage.Data[5]=I3&0xff;
	TxMessage.Data[6]=I4>>8;
	TxMessage.Data[7]=I4&0xff;
	
	    while((TransmitMailbox == CAN_TxStatus_NoMailBox) && (time_out_count++ != 0xFF))
    {
				TransmitMailbox = CAN_Transmit(CAN1, &TxMessage);
		}
		MyDelayus(20);
		

   i = 0;
	TransmitMailbox = CAN_TxStatus_NoMailBox;	
	time_out_count = 0;
	TxMessage.StdId=0x141;
	TxMessage.IDE=CAN_ID_STD;
	TxMessage.RTR=CAN_RTR_DATA;
	TxMessage.DLC=8;
	
	TxMessage.Data[0]=I5>>8;
	TxMessage.Data[1]=I5&0xff;
	TxMessage.Data[2]=I6>>8;
	TxMessage.Data[3]=I6&0xff;
	TxMessage.Data[4]=I7>>8;
	TxMessage.Data[5]=I7&0xff;
	TxMessage.Data[6]=I8>>8;
	TxMessage.Data[7]=I8&0xff;
	
	    while((TransmitMailbox == CAN_TxStatus_NoMailBox) && (time_out_count++ != 0xFF))
    {
				TransmitMailbox = CAN_Transmit(CAN1, &TxMessage);
		}
		
}

