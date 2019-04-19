#ifndef __MOVEMENT_BASIC_MATH_H
#define __MOVEMENT_BASIC_MATH_H

#include "math.h"
#include "stm32f4xx.h"
#include "arm_math.h"
#include <stdbool.h>
#include "movement.h"

/***运动模式的类型***/

/***Declare variables***/
extern const float speed_curve_area_radio;
extern const float angle_to_radian_radio;

/*********Function declaration*******/
/**
 * @brief: Calculate the ratio of expected velocity to 
           peak velocity according to the actual proportion
 * @param: 0-1 The ratio of change time to total time
 * @return: 0-1 Proportion of peak velocity
 * @status: 2019.4.15
 */
float LookUpDMSpeedTable(float value_t) ;

/**
 * @brief: Calculate the ratio of time spent to the
           whole period according to the distance proportion
 * @param: 0-1 The ratio of distance walked to the whole distance
 * @return: 0-1 Proportion of time spent
 * @status: 2019.4.15
 */
float LookUpDMTimeTable(float value_distance) ;


void CalDMMovementPosition();
													
void CalMovementSpeed();
void JudgeMovementSafiety();
float CalRealSpeed(float speed);
float CalRealDistance(float position_D_value);
	float CalRealPosition(float distance_D_value);
	float CalDMMinSafeDistance();
	float CalDMMaxSafeDistance();
#endif