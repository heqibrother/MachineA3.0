#ifndef __LOCATIONINFO_H
#define __LOCATIONINFO_H

#include "location.h"
/*********Function declaration*******/
/**
 * @brief: Load relative positioning data
 * @return: none
 * @status: 2019.4.21
 */
void GetRelativeLocation();

/**
 * @brief: Load laser positioning data
 * @return: none
 * @status: 2019.4.21
 */
void GetLaser1Location();

/**
 * @brief: Load laser radar positioning data
 * @return: none
 * @status: 2019.4.21
 */
void GetLaserRadarLocation();

/**
 * @brief: Update location information based on location 
           information acquired by schedule selection
 * @return: none
 * @status: 2019.4.21
 */
void RefreshCurrentPosition();

/**
 * @brief: use photoelectric switches to locate steps
 * @return: none
 * @status: 2019.4.22
 */
void GetStepLocationData();
#endif