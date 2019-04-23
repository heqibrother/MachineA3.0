/*   
   Constructing Fundamental Functions of Leg Motion
*/

#include "leg_movement.h"
LegState kLegState;
LegStateData leg_state_data;
LegDataFeedback leg_data_feedback;

void LegModeChange()
{
	leg_state_data.leg_state_number = leg_state_data.leg_state_number_pre;
	SendLegCommand();
}

void LayDown()
{
	switch(kLegState)
	{
		case kHighLegMove:
			LowlegLift();
			break;
		
		case kLowLegMove:
			HighlegLift();
			break;
		
		default:
			break;
	}
}
bool DetectLegRecoverPosition()
{
				if(kLegState == kHighLegMove)
		{
			if((leg_data_feedback.leg_state_[1] == 0|| leg_data_feedback.leg_state_[1] == 8)
			   &&(leg_data_feedback.leg_state_[3] == 0|| leg_data_feedback.leg_state_[3] == 8))
			{
				return true;
			}
		}
		else if(kLegState==kLowLegMove)
		{
					if((leg_data_feedback.leg_state_[0] == 0|| leg_data_feedback.leg_state_[0] == 8)
				 &&(leg_data_feedback.leg_state_[2] == 0|| leg_data_feedback.leg_state_[2] == 8)
					)
			{
				return true;
			}
		}
	return false;
}

bool DetectLegLayDownPosition()
{
				if(kLegState == kLowLegMove)
		{
			if((leg_data_feedback.leg_state_[0] == 1|| leg_data_feedback.leg_state_[0] == 9)
				 &&(leg_data_feedback.leg_state_[1] != 1|| leg_data_feedback.leg_state_[1] != 9)
				 &&(leg_data_feedback.leg_state_[2] == 1|| leg_data_feedback.leg_state_[2] == 9)
			   &&(leg_data_feedback.leg_state_[3] != 1|| leg_data_feedback.leg_state_[3] != 9))
			{
				return true;
			}
		}
		else if(kLegState==kHighLegMove)
		{
					if((leg_data_feedback.leg_state_[0] != 1|| leg_data_feedback.leg_state_[0] != 9)
				 &&(leg_data_feedback.leg_state_[1] == 1|| leg_data_feedback.leg_state_[1] == 9)
				 &&(leg_data_feedback.leg_state_[2] != 1|| leg_data_feedback.leg_state_[2] != 9)
			   &&(leg_data_feedback.leg_state_[3] == 1|| leg_data_feedback.leg_state_[3] == 9))
			{
				return true;
			}
		}
	return false;
}
bool LegPartAnswer()
{
	if(!leg_data_feedback.send_leg_change_flag)
	{
		return true;
	}
	return false;
}
bool TimeToLayDown()
{
	if(GetTimeLeft()<=GetTimeLayDownAdvance())
	{
		return true;
	}
	return false;
}

void HighlegLift()
{
	leg_state_data.leg_state_command = 0x1010;
  SendLegCommand();
}
void LowlegLift()
{
	leg_state_data.leg_state_command = 0x0101;
   SendLegCommand();
}

//void ChangeLeg(short I1, short I2,short I3,short I4)
//{
//	CanTxMsg TxMessage;
//	uint16_t i = 0;
//	uint8_t TransmitMailbox = CAN_TxStatus_NoMailBox;	
//	uint16_t  time_out_count = 0;
//	TxMessage.StdId=0x121;
//	TxMessage.IDE=CAN_ID_STD;
//	TxMessage.RTR=CAN_RTR_DATA;
//	TxMessage.DLC=8;
//	
//	TxMessage.Data[0]=I1>>8;
//	TxMessage.Data[1]=I1&0xff;
//	TxMessage.Data[2]=I2>>8;
//	TxMessage.Data[3]=I2&0xff;
//	TxMessage.Data[4]=I3>>8;
//	TxMessage.Data[5]=I3&0xff;
//	TxMessage.Data[6]=I4>>8;
//	TxMessage.Data[7]=I4&0xff;
//	
//	    while((TransmitMailbox == CAN_TxStatus_NoMailBox) && (time_out_count++ != 0xFF))
//    {
//				TransmitMailbox = CAN_Transmit(CAN1, &TxMessage);
//		}
//		
//}

void LegPartInit()
{
	leg_state_data.leg_target_state_time = 0;
	leg_state_data.leg_safe_to_laydown = 1;
	leg_state_data.leg_state_number = 0;
	kLegState = kHighLegMove;
}

int32_t GetTimeLayDownAdvance()
{
	int32_t result = 0;
	switch(leg_state_data.leg_state_number)
	{
		case 2:
			result = 90;
			break;
		
		case 3:
			result = 190;
			break;
		
		case 4:
			result = 190;
			break;
		
		case 5:
			result = 110;
			break;
		
		case 6:
			result = 110;
			break;
		
		case 7:
			result = 160;
			break;
		
		case 8:
			result = 250;
			break;
		
		case 9:
			result = 190;
			break;
		
		case 10:
			result = 90;
			break;
		
		default:
			break;
	}
	return result;
}

LegState ChangeLegState(LegState klegstate)
{
	if(klegstate == kHighLegMove)
	{
		return kLowLegMove; 
	}
	else if(klegstate == kLowLegMove)
	{
		return kHighLegMove;
	}
}

void SendLegCommand()
{
	//ChangeLeg(leg_state_data.leg_state_command,leg_state_data.leg_target_state_time,leg_state_data.leg_state_number,leg_state_data.leg_safe_to_laydown);
  leg_data_feedback.send_leg_change_flag = true;
}

void TaskLEGCOMMUNICATION(void *p_arg)
{
	  OS_ERR err;
    while(1)
    {
			if(leg_data_feedback.send_leg_change_flag == true)
			{
				//SendLegChange(1,2,3,4);
				SendLegChange(leg_state_data.leg_state_command,leg_state_data.leg_target_state_time,leg_state_data.leg_state_number,leg_state_data.leg_safe_to_laydown);
			}
	  	OSTimeDlyHMSM(0, 0, 0, 5, OS_OPT_TIME_HMSM_STRICT, &err);
	  }
}