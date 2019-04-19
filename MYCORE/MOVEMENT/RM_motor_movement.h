#ifndef __RM_MOTOR_MOVEMENT_H
#define __RM_MOTOR_MOVEMENT_H

#include "math.h"
#include "stm32f4xx.h"
#include "arm_math.h"
#include <stdbool.h>
#include "superstratum.h"
#include "DM_motor_movement.h"

extern const float RM_radio;
/***运动模式的类型***/

extern SpeedStage RM_speed_stage;
/*********Function declaration*******/

/**
 * @brief: Determining the Motion State of Rotate Motor
 * @return: none
 * @status: 2019.4.15
 */
void MoveRM();

/**
 * @brief:  The stage - stop
 * @return: none
 * @status: 2019.4.15
 */
void RMStopMove();

/**
 * @brief:  The stage - accelerate
 * @return: none
 * @status: 2019.4.15
 */
void RMAccelerate();

/**
 * @brief:  The stage - decelerate
 * @return: none
 * @status: 2019.4.15
 */
void RMDecelerate();

/**
 * @brief: Judging the Motion Stage of Rotate Motor -----RM_speed_stage
 * @return: none
 * @status: 2019.4.15
 */
void JudgeRMSpeedStage();

void RMPartInit();
#endif