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
