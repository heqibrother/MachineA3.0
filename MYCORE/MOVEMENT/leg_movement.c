/*   
   Constructing Fundamental Functions of Leg Motion
*/

#include "leg_movement.h"
enum LegState kLegState;
LegStateData leg_state_data;
void LegModeChange()
{
	
}
void LayDown()
{
	
}
bool DetectLegRecoverPosition()
{
	return false;
}
bool DetectLegLayDownPosition()
{
	return false;
}
bool LegPartAnswer()
{
	return false;
}
bool TimeToLayDown()
{
	
	return false;
}

void HighlegLift()
{
	ChangeLeg(0x1010,leg_state_data.leg_target_state_time,leg_state_data.leg_state_number,leg_state_data.leg_safe_to_laydown);
}
void LowlegLift()
{
  ChangeLeg(0x0101,leg_state_data.leg_target_state_time,leg_state_data.leg_state_number,leg_state_data.leg_safe_to_laydown);
}

void ChangeLeg(short I1, short I2,short I3,short I4)
{
	CanTxMsg TxMessage;
	uint16_t i = 0;
	uint8_t TransmitMailbox = CAN_TxStatus_NoMailBox;	
	uint16_t  time_out_count = 0;
	TxMessage.StdId=0x121;
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
		
}

void LegPartInit()
{
	leg_state_data.leg_target_state_time = 0;
	leg_state_data.leg_safe_to_laydown = 0;
	leg_state_data.leg_state_number = 0;
	kLegState = kHighLegMove;
}
