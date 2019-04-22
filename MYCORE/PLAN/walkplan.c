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
				break;
			}
			else 	if(machineA_general_data.stage_step_number == 2)
			{
			  SetBasicMotionParameters(300,100,0,kBothUnStablity,kSpeedFirst);
				break;
			} 			
			else 	if(machineA_general_data.stage_step_number == 3)
			{
			  SetBasicMotionParameters(300,100,0,kBothUnStablity,kSpeedFirst);
				break;
			}
			else 	if(machineA_general_data.stage_step_number == 4)
			{
			  SetBasicMotionParameters(300,100,0,kBothUnStablity,kSpeedFirst);
				break;
			}
				kMachineAState = kBeforeLaserDetect;
				machineA_general_data.stage_step_number = 1;
      			
			
    case kBeforeLaserDetect:

			if(location_data.current_position.ground_leg_y<Redline_Position_Prepare)
			{
			  SetBasicMotionParameters(300,100,0,kBothUnStablity,kSpeedFirst);
				break;
			}
				kMachineAState = kBeforeTurnLeft;
				machineA_general_data.stage_step_number = 1;

	  case kBeforeTurnLeft:
       if(location_data.current_position.ground_leg_y<Redline_Position_Y1-50)
			 {
         SetBasicMotionParameters(CalStepDistance(Redline_Position_Y1,location_data.current_position.ground_leg_y,300,kLowLegMove)
				  ,100,0,kBothUnStablity,kSpeedFirst);   
				 break;
			 }				 
			 	kMachineAState = kTurnLeft;
				machineA_general_data.stage_step_number = 1;
			 
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