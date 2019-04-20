#ifndef __LOCALCOMPUTING_H
#define __LOCALCOMPUTING_H

#include "location.h"
/*********Function declaration*******/
void ChangePositionRecord(enum LegState klegstate,PositionDataType *position);
float CalOpositionX(float rela_x,float rela_y,int which_turn);
float CalOpositionY(float rela_x,float rela_y,int which_turn);
#endif