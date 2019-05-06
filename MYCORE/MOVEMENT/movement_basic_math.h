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

/**
 * @brief: Calculate the acceleration and deceleration position and 
           distance according to the set target and speed mode
 * @param: Motor Data Structure Address
 * @return: none
 * @status: 2019.4.21
 */
void CalMovementPosition(MotorMoveState *motor);

/**
 * @brief: Correction of Expected Speed Based on Step Spacing
 * @param: max speed expected
 * @return: none
 * @status: 2019.4.21
 */
void CalMovementSpeed(int speed_max);

/**
 * @brief: Modification of Angles and Steps Based on Vehicle Size
 * @return: none
 * @status: 2019.4.21
 */
void JudgeMovementSafiety();

/**
 * @brief: Conversion of motor speed
 * @param: motor speed (°/min)
 * @return: real speed (mm/ms)
 * @status: 2019.4.21
 */
float CalRealSpeed(float speed);

/**
 * @brief: Conversion of motor position
 * @param: motor position (°)
 * @return: real distance (mm)
 * @status: 2019.4.21
 */
float CalRealDistance(float position_D_value);

/**
 * @brief: Conversion of real distance
 * @param: real distance (mm)
 * @return: motor position (°)
 * @status: 2019.4.21
 */
float CalRealPosition(float distance_D_value);

/**
 * @brief: Calculate the maximum step distance according to the angle
 * @return: the maximum step
 * @status: 2019.4.21
 */
float CalDMMinSafeDistance();

/**
 * @brief: Calculate the minimum step distance according to the angle
 * @return: the minimum step
 * @status: 2019.4.21
 */
float CalDMMaxSafeDistance();
float FloatSafeDivision(float divisor);
int32_t Int32_tSafeDivision(int32_t divisor);//dividend/divisor
void CalMovementPositionRestart(MotorMoveState *motor);
#endif