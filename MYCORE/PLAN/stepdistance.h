#ifndef __STEPDISTANCE_H
#define __STEPDISTANCE_H

#include "plan.h"

/*********Function declaration*******/
/**
 * @brief: Round integers
 * @param: float
 * @return: Rounded integers
 * @status: 2019.4.21
 */
int MyClose(float value);

/**
 * @brief: Take the lower bound integer
 * @param: float
 * @return: integers
 * @status: 2019.4.21
 */
int MyFloor(float value);

/**
 * @brief: Take the higher bound integer
 * @param: float
 * @return: integers
 * @status: 2019.4.21
 */
int MyCeil(float value);

/**
 * @brief: Compare sizes, take large value
 * @param: values compared
 * @return: larger number
 * @status: 2019.4.21
 */
float CompareMax(float value1,float value2);

/**
 * @brief: Compare sizes, take small value
 * @param: values compared
 * @return: smaller number
 * @status: 2019.4.21
 */
float CompareMin(float value1,float value2);

/**
 * @brief: Macroscopically Plan Number of Steps
 * @param: total distance,step distance expected,Parity of steps£¬*step_distance(wait return)
 * @return: number of steps
 * @status: 2019.4.21
 */
int CalStepNumber(float alldistance,float distancehope,int required_remainder,float *step_distance,float deviation);

/**
 * @brief: Macroscopically Plan Distacne of Steps
 * @param: expected position,ground_leg position,step distance expected,which leg need to be the position leg
 * @return: step_distance
 * @status: 2019.4.21
 */
float CalStepDistance(float targetposition,float currentposition,float distancehope,LegState targetleg,int *step_number_left,float safe_distance);

#endif