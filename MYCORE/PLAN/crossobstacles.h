#ifndef __CROSSOBSTACLES_H
#define __CROSSOBSTACLES_H

#include "plan.h"

/*********Function declaration*******/
/**
 * @brief: Calculating Step Spacing in Crossing Stage,and Set up Barrier Location
 * @param: max_step_distance,position of rope,position of ground leg,position of suspended leg,*obstacle
 * @return: suitable step_distance
 * @status: 2019.4.22
 */
float CrossRope(float distance_hope,float rope_position,float ground_leg_position,float suspend_leg_position,Obstacle *targetobstacle);

/**
 * @brief: Calculate whether to cross obstacles
 * @param: result_step_distance,distance to obstacle,max_step_distance,*obstacle
 * @return: whether to cross obstacles :true(yes),false(no)
 * @status: 2019.4.21
 */
bool ConsideStepDistance(float *result,float obstacle_distance,float distance_hope,Obstacle *targetobstacle);

/**
 * @brief: To overcome two obstacles, we need to judge the distance of the two obstacles separately.
 * @param: max_step_distance,position of rope,position of ground leg,position of suspended leg
 * @return: suitable step_distance
 * @status: 2019.4.22
 */
float DoubleJudgeCrossRope(float distance_hope,float rope_position1,float rope_position2,float ground_leg_position,float suspend_leg_position);
#endif