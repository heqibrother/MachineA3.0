#ifndef __PLAN_H
#define __PLAN_H

#include "superstratum.h"

#include "stepdistance.h"
#include "crossobstacles.h"
#include "walkplan.h"
/*********Function declaration*******/
/**
 * @brief: Designated General Motion Planning
 * @return: none
 * @status: 2019.4.21
 */
void MakePlan();

/**
 * @brief: Set the basic parameters for each step
 * @param: step_distance(mm),speed(¡ã/min),yaw(¡ã)£¬speed_curve,time_point_style
 * @return: none
 * @status: 2019.4.21
 */
void SetBasicMotionParameters(float targetpositiondistance,float targetpositionspeed,float targetyaw,SpeedMode speedmode,MovementStyle movementstyle);

/**
 * @brief: Judge whether the last step is over
 * @return: true(last walk is over) false(not)
 * @status: 2019.4.21
 */
bool LastWalkOver();

#endif