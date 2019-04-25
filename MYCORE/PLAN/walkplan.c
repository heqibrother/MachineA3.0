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
         SetBasicMotionParameters(CalStepDistance(Redline_Position_Y1,location_data.current_position.ground_leg_y,300,RedFieldLeg(kLowLegMove))
				  ,100,0,kBothUnStablity,kSpeedFirst);   
				 break;
			 }				 
			 	kMachineAState = kTurnLeft;
				machineA_general_data.stage_step_number = 1;
			 
	  case kTurnLeft:  
		   leg_state_data.leg_state_number_pre = 3;
        if(machineA_general_data.stage_step_number == 1)
			{
			  SetBasicMotionParameters(220,100,45*field_direction,kBothUnStablity,kLocationFirst);
				break;
			}
			  kMachineAState = kBothLegTurnLeft;
				machineA_general_data.stage_step_number = 1;
			
	  case kBothLegTurnLeft:
			 leg_state_data.leg_state_number_pre = 4;
			   if(machineA_general_data.stage_step_number == 1)
			{
			  SetBasicMotionParameters(350,100,45*field_direction,kBothUnStablity,kLocationFirst);
				break;
			}
			  kMachineAState = kBeforeStepUp;
				machineA_general_data.stage_step_number = 1;
			
	  case kBeforeStepUp: 
			if(!leg_data_feedback.crossed_step)
			{
				SetBasicMotionParameters(350,100,45*field_direction,kBothUnStablity,kLocationFirst);
				break;
			}
			kMachineAState = kStepUp;
			machineA_general_data.stage_step_number = 1;
			
	  case kStepUp:
     		if(machineA_general_data.stage_step_number == 1)
			{
			  SetBasicMotionParameters(Distance_Beyond_Step - location_data.ground_leg_after_step,100,45*field_direction,kBothUnStablity,kLocationFirst);
				SetObstacleLocation(location_data.suspend_leg_before_step,0,&obstacle1);
				break;
			}
			  kMachineAState = kClimbOverTheStep;
				machineA_general_data.stage_step_number = 1;
		
	  case kClimbOverTheStep:  
      if(machineA_general_data.stage_step_number == 1)
			{
			  SetBasicMotionParameters(300,100,45*field_direction,kBothUnStablity,kLocationFirst);
				SetObstacleLocation(location_data.ground_leg_before_step,0,&obstacle1);
				break;
			}			
			if(machineA_general_data.stage_step_number == 2)
			{
			  SetBasicMotionParameters(300,100,60*field_direction,kBothUnStablity,kLocationFirst);
				break;
			}
			kMachineAState = kBeforeTurnRight;
			machineA_general_data.stage_step_number = 1;
			
	  case kBeforeTurnRight:  
			if(leg_data_feedback.crossd_step_state == 2||machineA_general_data.stage_step_number == 2)
			{
				leg_state_data.leg_state_number_pre = 7;
			}
     if(location_data.current_position.ground_leg_x<Oblique_PositionTurn_X-50)
		 {
			   SetBasicMotionParameters(CalStepDistance(Oblique_PositionTurn_X,location_data.current_position.ground_leg_x,
			                                             300*arm_cos_f32(60*angle_to_radian_radio),RedFieldLeg(kHighLegMove))/arm_cos_f32(60*angle_to_radian_radio)
				  ,100,60*field_direction,kBothUnStablity,kSpeedFirst);   
				 break;
		 }
		 kMachineAState = kTurnRight;
		 machineA_general_data.stage_step_number = 1;
		
	  case kTurnRight:
      leg_state_data.leg_state_number_pre = 8;			
     	if(machineA_general_data.stage_step_number == 1)
			{
			  SetBasicMotionParameters(180,50,0,kBothUnStablity,kLocationFirst);
				break;
			}
			kMachineAState = kBothLegTurnRight;
			machineA_general_data.stage_step_number = 1;
			
	  case kBothLegTurnRight:   
       if(machineA_general_data.stage_step_number == 1&&(location_data.current_position.ground_leg_y<Rope_Psition_Y1 - 100-400))
			{
			  SetBasicMotionParameters(100,100,0,kBothUnStablity,kLocationFirst);
				break;
			}
			kMachineAState = kBeforeCrossTheFirstRope;
			machineA_general_data.stage_step_number = 1;			
			
	  case kBeforeCrossTheFirstRope:
			 if(location_data.current_position.ground_leg_y<Rope_Psition_Y1 - 120-50)
			 {
				 SetBasicMotionParameters(CalStepDistance(Rope_Psition_Y1 - 120,location_data.current_position.ground_leg_y,300,kAnyLegMove)
				  ,100,0,kBothUnStablity,kLocationFirst);     
				 break;
			 }
			 	kMachineAState = kCrossTheFirstRope;
		  	machineA_general_data.stage_step_number = 1;	
		
	  case kCrossTheFirstRope:  
			if(machineA_general_data.stage_step_number == 1)
			{
			  SetBasicMotionParameters(CrossRope(300,Rope_Psition_Y1,location_data.current_position.ground_leg_y,location_data.current_position.suspend_leg_y,&obstacle1)
				                          ,100,0,kBothUnStablity,kLocationFirst);	
				break;
			}
			kMachineAState = kBeforeCrossTheSecondRope;
			machineA_general_data.stage_step_number = 1;
			
	  case kBeforeCrossTheSecondRope:
			 if(location_data.current_position.ground_leg_y<Rope_Psition_Y2 - 120-100)
			{
					if(location_data.current_position.ground_leg_y>Rope_Psition_Y2 - 100-350)
					{
						SetBasicMotionParameters(CrossRope(Rope_Psition_Y2 - 120-location_data.current_position.ground_leg_y,
						                        Rope_Psition_Y1,location_data.current_position.ground_leg_y,location_data.current_position.suspend_leg_y,&obstacle1)
				                          ,100,0,kBothUnStablity,kLocationFirst);	
					}
					else
					{
					SetBasicMotionParameters(CrossRope(350,Rope_Psition_Y1,location_data.current_position.ground_leg_y,location_data.current_position.suspend_leg_y,&obstacle1)
																		,100,0,kBothUnStablity,kLocationFirst);	
					}
			}
		  kMachineAState = kCrossTheSecondRope;
			machineA_general_data.stage_step_number = 1;

	  case kCrossTheSecondRope:
			if(machineA_general_data.stage_step_number == 1)
			{
			  SetBasicMotionParameters(DoubleJudgeCrossRope(300,Rope_Psition_Y1,Rope_Psition_Y2,location_data.current_position.ground_leg_y,location_data.current_position.suspend_leg_y)
				                          ,100,0,kBothUnStablity,kLocationFirst);	
				break;
			}
			kMachineAState = kArriveThePost;
			machineA_general_data.stage_step_number = 1;
			
	  case kArriveThePost:  
				if((location_data.current_position.highleg_y>=Hill_Position_Y||location_data.current_position.lowleg_y>=Hill_Position_Y)&&machineA_general_data.stage_step_number<6)
			{
				machineA_general_data.stage_step_number = 6;
			}	
		
		 	if(machineA_general_data.stage_step_number == 1)
			{
			  SetBasicMotionParameters(CrossRope(350,Rope_Psition_Y2,location_data.current_position.ground_leg_y,location_data.current_position.suspend_leg_y,&obstacle1)
				                        ,100,0,kBothUnStablity,kSpeedFirst);
				break;
			}
			else 	if(machineA_general_data.stage_step_number == 2)
			{
				SetBasicMotionParameters(CrossRope(350,Rope_Psition_Y2,location_data.current_position.ground_leg_y,location_data.current_position.suspend_leg_y,&obstacle1)
												,100,0,kBothUnStablity,kSpeedFirst);
				break;
			} 			
			else 	if(machineA_general_data.stage_step_number == 3)
			{
			  SetBasicMotionParameters(CrossRope(350,Rope_Psition_Y2,location_data.current_position.ground_leg_y,location_data.current_position.suspend_leg_y,&obstacle1)
				                        ,100,0,kBothUnStablity,kSpeedFirst);
				break;
			}
			else 	if(machineA_general_data.stage_step_number == 4)
			{
			  SetBasicMotionParameters(CrossRope(350,Rope_Psition_Y2,location_data.current_position.ground_leg_y,location_data.current_position.suspend_leg_y,&obstacle1)
				                        ,100,0,kBothUnStablity,kSpeedFirst);
				break;
			}
			else 	if(machineA_general_data.stage_step_number == 5)
			{
			  SetBasicMotionParameters(CrossRope(350,Rope_Psition_Y2,location_data.current_position.ground_leg_y,location_data.current_position.suspend_leg_y,&obstacle1)
				                        ,100,0,kBothUnStablity,kSpeedFirst);
				break;
			}
			else 	if(machineA_general_data.stage_step_number == 6)
			{
			  SetBasicMotionParameters(CrossRope(100,Rope_Psition_Y2,location_data.current_position.ground_leg_y,location_data.current_position.suspend_leg_y,&obstacle1)
				                        ,100,0,kBothUnStablity,kSpeedFirst);
				break;
			}
			kMachineAState = kClamberMode;
			machineA_general_data.stage_step_number = 1;
		
		case kClamberMode: 
			 leg_state_data.leg_state_number_pre = 2;
      if(machineA_general_data.stage_step_number == 1)
			{
			  SetBasicMotionParameters(0,100,0,kBothUnStablity,kClamberPrepare);
				if(kLegState == kHighLegMove)
				{
					DM_MoveInfo.distance_data.target_distance = (Aluminum_Tube_Width/2 + 5)/DM_radio;
				}
				else
				{
					DM_MoveInfo.distance_data.target_distance = -(Aluminum_Tube_Width/2 + 5)/DM_radio;
				}
				break;
			}
			kMachineAState = kClamberReady;
			machineA_general_data.stage_step_number = 1;
			
		case kClamberReady:     
      kMachineAGeneralState = kClamberModeWaiting;	
		  machineA_general_data.stage_step_number = 1;
		break;
		
	  case kClamber:  
      if(machineA_general_data.stage_step_number == 1)
			{
				 leg_state_data.leg_state_number_pre = 9;
				SetLegLengthLow(100,75,20,70);
			  SetBasicMotionParameters(340,150,0,kBothUnStablity,kClamberWorking);
				break;
			}
		 	if(machineA_general_data.stage_step_number == 2)
			{
				SetLegLengthLow(60,80,100,50);
			  SetBasicMotionParameters(300,150,0,kClamberSpecialCurve,kClamberWorking);
				break;
			}			
			if(machineA_general_data.stage_step_number == 3)
			{
        SetLegLengthLow(60,60,70,60);
			  SetBasicMotionParameters(300,150,0,kClamberSpecialCurve,kClamberWorking);
				break;
			}
			if(machineA_general_data.stage_step_number == 4)
			{
								leg_state_data.leg_state_number_pre = 5;
				SetLegLengthLow(50,50,50,50);
			  SetBasicMotionParameters(300,180,0,kClamberSpecialCurve,kClamberWorking);
				break;
			}
			if(machineA_general_data.stage_step_number == 5)
			{
			  SetBasicMotionParameters(300,220,0,kClamberSpecialCurve,kClamberWorking);
				break;
			}
			if(fabs(leg_angle.original_pitch)<4)
			{
				kMachineAState = kReachSummit;
				machineA_general_data.stage_step_number = 1;
			} 
			else
			{
				SetBasicMotionParameters(300,250,0,kClamberSpecialCurve,kClamberWorking);
				break;
			}
			
	  case kReachSummit: 
			if(machineA_general_data.stage_step_number == 1)
			{
			  SetBasicMotionParameters(100,100,0,kClamberSpecialCurve,kSpeedFirst);
				break;
			}
        leg_state_data.leg_state_number_pre = 6;
			  leg_state_data.leg_state_number = 6;
			  SteadyLegMode();
			  LegModeChange();	
        kMachineAGeneralState = kMachineError;			
		default:
			break;
	}
}