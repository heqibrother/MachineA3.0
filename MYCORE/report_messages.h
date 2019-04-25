#ifndef __REPORT_MESSAGES_H
#define __REPORT_MESSAGES_H

#include "superstratum.h"


/*********Function declaration*******/
/**
 * @brief: Return data and record with txt
 * @return: none
 * @status: 2019.4.21
 */
void ReportMessage();

/**
 * @brief: Return data and draw waveforms
 * @return: none
 * @status: 2019.4.21
 */
void ReportCurve();//·µ»ØÊý¾Ý

/**
 * @brief: Return data and record with txt about position
 * @return: none
 * @status: 2019.4.23
 */
void ReportPositionY();

/**
 * @brief: Return data and record with txt about machine state
 * @return: none
 * @status: 2019.4.23
 */
void ReportState();
void ReportLegState();
void ReportLegStateYaw();
void ReportStepPosition();
void ReportPositionX();
void ReportClamberLegState();
#endif