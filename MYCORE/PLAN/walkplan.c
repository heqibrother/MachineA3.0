#include "walkplan.h"

void WalkPlan()
{
	switch(kMachineAState)
	{
    case kBeforeStart:
			kMachineAState = kStart;
		case kStart:
		 	if(machineA_general_data.stage_step_number == 1)
			{
			  SetBasicMotionParameters(300,100,0,kBothUnStablity,kSpeedFirst);
			}
			else 	if(machineA_general_data.stage_step_number == 2)
			{
			  SetBasicMotionParameters(300,100,0,kBothUnStablity,kSpeedFirst);
			} 			
			else 	if(machineA_general_data.stage_step_number == 3)
			{
			  SetBasicMotionParameters(300,100,0,kBothUnStablity,kSpeedFirst);
			}
			else 	if(machineA_general_data.stage_step_number == 4)
			{
			  SetBasicMotionParameters(300,100,0,kBothUnStablity,kSpeedFirst);
			}
			if(machineA_general_data.stage_step_number > 4)
			{
				kMachineAState = kBeforeLaserDetect;
				machineA_general_data.stage_step_number = 1;
			}
      else break;			
    case kBeforeLaserDetect:   
	  case kBeforeTurnLeft:      
	  case kTurnLeft:             
	  case kBothLegTurnLeft:
	  case kBeforeStepUp:         
	  case kStepUp:             
	  case kClimbOverTheStep:      
	  case kBeforeTurnRight:      
	  case kTurnRight:       
	  case kBothLegTurnRight:     
	  case kBeforeCrossTheFirstRope:
	  case kCrossTheFirstRope:  
	  case kBeforeCrossTheSecondRope:
	  case kCrossTheSecondRope:
	  case kArriveThePost:          
	  case kStopAtPost:    
		
		default:
			break;
	}
}