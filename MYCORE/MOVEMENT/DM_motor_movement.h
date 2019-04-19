#ifndef __DM_MOTOR_MOVEMENT_H
#define __DM_MOTOR_MOVEMENT_H

/***�˶�״̬***///��.h�ļ�����ǰ���壬��RM.h�л���ʵ����extern�������������ⱨ��
typedef enum 
{
	kStopMove,   	
	kAccelerate,
	kKeepSpeed,
	kDeccelerate,
}SpeedStage;//����ٶȹ滮�ĸ���״̬

#include "math.h"
#include "stm32f4xx.h"
#include "arm_math.h"
#include <stdbool.h>
#include "superstratum.h"

static const float DM_radio = 0.57596;//   66pi��3.141592654��/360  //motor_angle * radio = real distance



extern SpeedStage DM_speed_stage;
/*********Function declaration*******/
/**
 * @brief: Determining the Motion State of Direct Motor
 * @return: none
 * @status: 2019.4.15
 */
void MoveDM();

/**
 * @brief: Judging the Motion Stage of Direct Motor -----DM_speed_stage
 * @return: none
 * @status: 2019.4.15
 */
void JudgeDMSpeedStage();

/**
 * @brief: The stage - stop
 * @return: none
 * @status: 2019.4.15
 */
void DMStopMove();

/**
 * @brief: The stage - accelerate
 * @return: none
 * @status: 2019.4.15
 */
void DMAccelerate();

/**
 * @brief: The stage - keep speed
 * @return: none
 * @status: 2019.4.15
 */
void DMKeepSpeed();

/**
 * @brief: The stage - decelerate
 * @return: none
 * @status: 2019.4.15
 */
void DMDeccelerate();

/**
 * @brief: Balancing the Speed of Acceleration State of Motor
 * @return: none
 * @status: 2019.4.15
 */
float SuitableAccelerateSpeed();

/**
 * @brief: Balancing the Speed of Deceleration State of Motor
 * @return: none
 * @status: 2019.4.15
 */
float SuitableDecelerateSpeed();

/**
 * @brief: Judging whether the operation of direct motor has entered a certain stage
 * @param: position of motor , position needed to judge
 * @return: true(reached)/false(not)
 * @status: 2019.4.15
 */
bool JugdeStageTool(float value_a,float value_b);

void DMPartInit();
void SetSpeedDirection();
#endif