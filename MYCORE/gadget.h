#ifndef __GADGET_H
#define __GADGET_H

#include "superstratum.h"

/***��е����***/
typedef struct 
{
   int16_t take_token_state;
   int16_t lift_token_state;
	 bool organ_message_send_flag;
}Organs;

extern Organs organ;
/*********Function declaration*******/
void OrgansInit();
void OrganCommand();

#endif