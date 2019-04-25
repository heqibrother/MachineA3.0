#include "gadget.h"

Organs organ;
//void TakeToken()
//{
//	command_data[0] = 1;
//	SM_command(command_data[0],command_data[1],command_data[2],command_data[3]);
//}

//void LiftToken()
//{
//	command_data[1] = 1;
//	SM_command(command_data[0],command_data[1],command_data[2],command_data[3]);
//}

void OrgansInit()
{
	organ.take_token_state = 0;
	organ.lift_token_state = 0;
	organ.organ_message_send_flag = false;
}

void OrganCommand()
{
	SendOrganCommand(organ.take_token_state,organ.take_token_state,0,0);
}

LegState RedFieldLeg(LegState target_leg_state)
{
	if(target_leg_state == kHighLegMove)
	{
	   if(field_direction>0)
	    return kHighLegMove;
	  else
		  return kLowLegMove;
	}
	else if(target_leg_state == kLowLegMove)
	{
		if(field_direction>0)
	    return kLowLegMove;
	  else
		  return kHighLegMove;
	}
	kMachineAGeneralState = kMachineError;
	return kAnyLegMove;
}

void RedFieldLegLift(LegState target_leg_state)
{
		if(target_leg_state == kHighLegMove)
	{
	   if(field_direction>0)
	    HighlegLift();
	  else
		  LowlegLift();
	}
	else if(target_leg_state == kLowLegMove)
	{
		if(field_direction>0)
	    LowlegLift();
	  else
		  HighlegLift();
	}
}

