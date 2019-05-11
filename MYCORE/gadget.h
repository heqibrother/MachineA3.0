#ifndef __GADGET_H
#define __GADGET_H

#include "superstratum.h"

/***»úÐµ¿ª¹Ø***/
typedef struct 
{
   int16_t take_token_state;
   int16_t lift_token_state;
	 int16_t camera_angle;
	 bool organ_message_send_flag;
}Organs;

extern Organs organ;
/*********Function declaration*******/
void OrgansInit();
void OrganCommand();
LegState RedFieldLeg(LegState target_leg_state);
void RedFieldLegLift(LegState target_leg_state);
void LiftToken();
void TakeToken();
void SetCameraAngle(int16_t set_angle);

void SetCamera(int16_t set_angle);
float CalSuitableLegMove(float original_data,float radio);
#endif