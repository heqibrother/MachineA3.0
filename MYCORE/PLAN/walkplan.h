#ifndef __WALKPLAN_H
#define __WALKPLAN_H

#include "plan.h"

typedef enum
{
	kRadicalStrategy,
  kNeutralStrategy,
  kConservativeStrategy,
}StrategyAttribute;

extern StrategyAttribute kstrategyattribute;
/*********Function declaration*******/

/**
 * @brief: Plan step distance, angle and speed in normal walking
 * @return: none
 * @status: 2019.4.21
 */
void WalkPlan();
#endif