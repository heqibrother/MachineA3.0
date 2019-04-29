#ifndef __LOCALCOMPUTING_H
#define __LOCALCOMPUTING_H

#include "location.h"
/*********Function declaration*******/

/**
 * @brief: Update the information of the other leg based on the information of one leg
 * @param: Trusted leg£¬Updated data structure pointer
 * @return: none
 * @status: 2019.4.21
 */
void ChangePositionRecord(LegState klegstate,PositionDataType *position,MotorMoveState *motorstate);

/**
 * @brief: Calculate the X-Direction Distance between the Location of the 
           Vehicle and the Location of the Zero Point of the Vehicle
 * @param: X coordinates of position£¨Left and right negative£©£¬Y coordinates of position£¬On which leg
 * @return: X of target - X of origin
 * @status: 2019.4.21
 */
float CalOpositionX(float rela_x,float rela_y,int which_turn);

/**
 * @brief: Calculate the Y-Direction Distance between the Location of the 
           Vehicle and the Location of the Zero Point of the Vehicle
 * @param: X coordinates of position£¨Left and right negative£©£¬Y coordinates of position£¬On which leg
 * @return: Y of target - Y of origin
 * @status: 2019.4.21
 */
float CalOpositionY(float rela_x,float rela_y,int which_turn);
void SetLegsInitialPosition(float set_x,float set_y);
#endif