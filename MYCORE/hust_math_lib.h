/* (C) COPYRIGHT @Hust-Robocon-Team 2019 */

#ifndef HUST_MATH_LIB_H_
#define HUST_MATH_LIB_H_
#include "math.h"
/** Notice: all functions here should be fast,
 *          useful, independent and fully-tested.
 *  Designer should avoid possible mistakes by users */

#ifdef __cplusplus
 extern "C" {
#endif
/**
 * @brief: atan2() function using look-up-table method, fast and accurate
 * @param: y, x
 * @return: atan2 value in [-pi, pi], including phase information
 * @unit: rad
 * @status: 2019.1.23 tested(chengjie), function well and fast, accuracy: 0.00001
 */
float FastTableAtan2(float y, float x) __attribute__((pure));

/**
 * @brief: Base On FastTableAtan2 but return value in [0, 2pi];
 */
float FastTableAtan2Positive(float y, float x) __attribute__((pure));

/**
 * @brief: atan() function using look-up-table method, fast and accurate
 * @param: tan value
 * @return: atan value in [-pi, pi]
 * @unit: rad
 * @status: 2019.1.17 tested(chengjie)
 * @reference: Abhisek Ukil. Vishal H Shah. Bernhard Deck. Fast Computation of
 *  arctangent Functions for Embedded Applications: A Comparative
 *  Analysis. IEEE.2011
 */
float FastTableAtan(float tan_value) __attribute__((pure));

/**
 * @brief: acos() function using FastTableAtan() method
 * @param: cos value in [-1, 1], if cos_value > 1 return 0.0
 * @return: acos value in [0, pi]
 * @unit: rad
 * @status: 2019.1.26 tested(chengjie)
 */
float FastAcos(float cos_value) __attribute__((pure));

/**
 * @brief: normalize angle to [-pi, pi] in an elegant way
 * @param: angle_rad to be normalized
 * @return: normalized angle
 * @unit: rad
 * @status: 2019.1.17 tested(chengjie), works
 * @reference: apollo open source autonomous driving platform
 */
float NormalizeAngle(float angle_rad) __attribute__((pure));

/**
 * @brief: normalize angle to [0, 2pi] in an elegant way
 * @param: angle_rad to be normalized
 * @return: normalized angle
 * @unit: rad
 * @status: 2019.1.17 tested(chengjie), works
 */
float NormalizeAnglePositive(float angle_rad) __attribute__((inline, pure));

/**
 * @brief: limit raw_data to [lowwer_bound, upper_bound]
 * @param: data to limit, lowwer_bound, upper_bound
 * @return: limited value
 * @status: 2019.1.24 tested(chengjie), function well
 */
float Clamp(float raw_data, float lowwer_bound, float upper_bound)
    __attribute__((inline, pure));


float FastAcos(float cos_value);
#ifdef __cplusplus
}
#endif

#endif  // HUST_MATH_LIB_H_
