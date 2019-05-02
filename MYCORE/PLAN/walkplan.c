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
			  SetBasicMotionParameters(300,220,0,kBothUnStablity,kSpeedFirst);
				break;
			}
			else if(machineA_general_data.stage_step_number == 2)
			{
			  SetBasicMotionParameters(300,280,0,kBothUnStablity,kSpeedFirst);
				break;
			} 			
			else 	if(machineA_general_data.stage_step_number == 3)
			{
			  SetBasicMotionParameters(300,360,0,kBothUnStablity,kSpeedFirst);
				break;
			}
			else 	if(machineA_general_data.stage_step_number == 4)
			{
			  SetBasicMotionParameters(300,450,0,kBothUnStablity,kSpeedFirst);
				break;
			}
				kMachineAState = kBeforeLaserDetect;
				machineA_general_data.stage_step_number = 1;
      			
			
    case kBeforeLaserDetect:
			if(location_data.current_position.ground_leg_y<current_field.first_line_pre_position.y)
			{
			  SetBasicMotionParameters(300,450,0,kBothUnStablity,kSpeedFirst);
				break;
			}
				kMachineAState = kBeforeTurnLeft;
				machineA_general_data.stage_step_number = 1;

	  case kBeforeTurnLeft:
			machineA_general_data.target_distance = CalStepDistance(current_field.first_line_position.y,location_data.current_position.ground_leg_y,
		                                      300,RedFieldLeg(kLowLegMove),&machineA_general_data.step_number_left,50.0f);
       if(machineA_general_data.step_number_left!=0)
			 {
         SetBasicMotionParameters(machineA_general_data.target_distance
				  ,200,0,kBothUnStablity,kSpeedFirst);   
				 break;
			 }				 
			//  kMachineAGeneralState = kMachineError;
			 	kMachineAState = kTurnLeft;
				machineA_general_data.stage_step_number = 1;
			 
	  case kTurnLeft:  
		   leg_state_data.leg_state_number_pre = 3;
        if(machineA_general_data.stage_step_number == 1)
			{
			  SetBasicMotionParameters(200,100,45*field_direction,kBothUnStablity,kRisingTurn);
				break;
			}
			  kMachineAState = kBothLegTurnLeft;
				machineA_general_data.stage_step_number = 1;
			
	  case kBothLegTurnLeft:
			 //leg_state_data.leg_state_number_pre = 3;
		   leg_state_data.leg_state_number_pre = 4;
			   if(machineA_general_data.stage_step_number == 1)
			{
			  SetBasicMotionParameters(300,150,45*field_direction,kBothUnStablity,kRisingTurn);
				break;
			}
			  kMachineAState = kBeforeStepUp;
				machineA_general_data.stage_step_number = 1;
			
	  case kBeforeStepUp: 
			if(!leg_data_feedback.crossed_step)
			{
				SetBasicMotionParameters(300,180,45*field_direction,kBothUnStablity,kLocationFirst);
				break;
			}
			kMachineAState = kStepUp;
			machineA_general_data.stage_step_number = 1;
			
	  case kStepUp:
     		if(machineA_general_data.stage_step_number == 1)
			{
			  SetBasicMotionParameters(Distance_Beyond_Step - location_data.ground_leg_after_step,100,45*field_direction,kBothUnStablity,kCrossStep);
				SetObstacleLocation(location_data.suspend_leg_before_step,0,&obstacle1);
				break;
			}
			  kMachineAState = kClimbOverTheStep;
				machineA_general_data.stage_step_number = 1;
		
	  case kClimbOverTheStep:  
      if(machineA_general_data.stage_step_number == 1)
			{
			  SetBasicMotionParameters(300,150,45*field_direction,kBothUnStablity,kCrossStep);
				//SetObstacleLocation(location_data.ground_leg_before_step,0,&obstacle1);
				break;
			}			
			if(machineA_general_data.stage_step_number == 2)
			{
			  SetBasicMotionParameters(300,150,60*field_direction,kBothUnStablity,kCrossStep);
			//	SetObstacleLocation(location_data.ground_leg_before_step,0,&obstacle1);
				break;
			}
			if(machineA_general_data.stage_step_number == 3)
			{
				leg_state_data.leg_state_number_pre = 11;
			  SetBasicMotionParameters(300,150,60*field_direction,kFlexibleSteady,kCrossedStep);
				break;
			}
			//kMachineAGeneralState = kMachineError;
			kMachineAState = kBeforeTurnRight;
			machineA_general_data.stage_step_number = 1;
			
	  case kBeforeTurnRight:  
//			if(leg_data_feedback.crossd_step_state == 2&&machineA_general_data.stage_step_number >= 1)
//			{
//				leg_state_data.leg_state_number_pre = 11;
//			}
				machineA_general_data.target_distance = CalStepDistance(current_field.second_turn_position.x,location_data.current_position.ground_leg_x,
			                                             280*arm_cos_f32(60*angle_to_radian_radio),RedFieldLeg(kHighLegMove),&machineA_general_data.step_number_left,70.0f*arm_cos_f32(60*angle_to_radian_radio))
			                                          /arm_cos_f32(60*angle_to_radian_radio);
     if(machineA_general_data.step_number_left!=0)
		 {
			   SetBasicMotionParameters(machineA_general_data.target_distance
				  ,150,60*field_direction,kFlexibleSteady,kSpeedFirst);   
				 break;
		 }
		 kMachineAState = kTurnRight;
		// kMachineAGeneralState = kMachineError;
		 machineA_general_data.stage_step_number = 1;
		
	  case kTurnRight:
      SetCamera(0);
     	if(machineA_general_data.stage_step_number == 1)
			{
			  SetBasicMotionParameters(180,100,0,kFlexibleSteady,kLocationFirst);
				break;
			}
		//	kMachineAGeneralState = kMachineError;
			kMachineAState = kBothLegTurnRight;
			machineA_general_data.stage_step_number = 1;
			
	  case kBothLegTurnRight:  
			leg_state_data.leg_state_number_pre = 8; 
       if(machineA_general_data.stage_step_number == 1&&(location_data.current_position.ground_leg_y<current_field.first_rope_position.y -2*Half_Length- 100-400))
			{
			  SetBasicMotionParameters(100,100,0,kFlexibleSteady,kRisingTurn);
				break;
			}
			kMachineAState = kBeforeCrossTheFirstRope;
			machineA_general_data.stage_step_number = 1;			
			
	  case kBeforeCrossTheFirstRope:
			machineA_general_data.target_distance = CalStepDistance(current_field.first_rope_position.y-2*Half_Length - 120,
		                                            location_data.current_position.ground_leg_y,300,kAnyLegMove,&machineA_general_data.step_number_left,50.0f);
			 if(machineA_general_data.step_number_left!=0)
			 {
				 SetBasicMotionParameters(machineA_general_data.target_distance
				  ,100,0,kBothUnStablity,kLocationFirst);     
				 break;
			 }
			 	kMachineAState = kCrossTheFirstRope;
		  	machineA_general_data.stage_step_number = 1;	
		
	  case kCrossTheFirstRope:  
			if(machineA_general_data.stage_step_number == 1)
			{
			  SetBasicMotionParameters(CrossRope(300,current_field.first_rope_position.y,location_data.current_position.ground_leg_y,location_data.current_position.suspend_leg_y,&obstacle1)
				                          ,100,0,kBothUnStablity,kLocationFirst);	
				break;
			}
			kMachineAState = kBeforeCrossTheSecondRope;
			machineA_general_data.stage_step_number = 1;
			
	  case kBeforeCrossTheSecondRope:
			 if(location_data.current_position.ground_leg_y<current_field.second_rope_position.y-2*Half_Length - 120-100)
			{
					if(location_data.current_position.ground_leg_y>current_field.second_rope_position.y-2*Half_Length  - 100-350)
					{
						SetBasicMotionParameters(CrossRope(current_field.second_rope_position.y-2*Half_Length  - 90-location_data.current_position.ground_leg_y,
						                        current_field.first_rope_position.y ,location_data.current_position.ground_leg_y,location_data.current_position.suspend_leg_y,&obstacle1)
				                          ,100,0,kBothUnStablity,kLocationFirst);	
					}
					else
					{
					SetBasicMotionParameters(CrossRope(350,current_field.first_rope_position.y,location_data.current_position.ground_leg_y,location_data.current_position.suspend_leg_y,&obstacle1)
																		,100,0,kBothUnStablity,kLocationFirst);	
					}
					break;
			}
		  kMachineAState = kCrossTheSecondRope;
			machineA_general_data.stage_step_number = 1;

	  case kCrossTheSecondRope:
			if(machineA_general_data.stage_step_number == 1)
			{
			  SetBasicMotionParameters(DoubleJudgeCrossRope(300,current_field.first_rope_position.y,current_field.second_rope_position.y,location_data.current_position.ground_leg_y,location_data.current_position.suspend_leg_y)
				                          ,100,0,kBothUnStablity,kLocationFirst);	
				break;
			}
			kMachineAState = kArriveThePost;
			machineA_general_data.stage_step_number = 1;
			
	  case kArriveThePost:  
				if((location_data.current_position.highleg_y>=current_field.hill_position.y||location_data.current_position.lowleg_y>=current_field.hill_position.y)&&machineA_general_data.stage_step_number<6)
			{
				machineA_general_data.stage_step_number = 6;
			}	
		
		 	if(machineA_general_data.stage_step_number == 1)
			{
			  SetBasicMotionParameters(CrossRope(350,current_field.second_rope_position.y,location_data.current_position.ground_leg_y,location_data.current_position.suspend_leg_y,&obstacle1)
				                        ,100,0,kBothUnStablity,kLocationFirst);
				break;
			}
			else 	if(machineA_general_data.stage_step_number == 2)
			{
				SetBasicMotionParameters(CrossRope(350,current_field.second_rope_position.y,location_data.current_position.ground_leg_y,location_data.current_position.suspend_leg_y,&obstacle1)
												,100,0,kBothUnStablity,kLocationFirst);
				break;
			} 			
			else 	if(machineA_general_data.stage_step_number == 3)
			{
			  SetBasicMotionParameters(CrossRope(350,current_field.second_rope_position.y,location_data.current_position.ground_leg_y,location_data.current_position.suspend_leg_y,&obstacle1)
				                        ,100,0,kBothUnStablity,kLocationFirst);
				break;
			}
			else 	if(machineA_general_data.stage_step_number == 4)
			{
			  SetBasicMotionParameters(CrossRope(350,current_field.second_rope_position.y,location_data.current_position.ground_leg_y,location_data.current_position.suspend_leg_y,&obstacle1)
				                        ,100,0,kBothUnStablity,kLocationFirst);
				break;
			}
			else 	if(machineA_general_data.stage_step_number == 5)
			{
			  SetBasicMotionParameters(CrossRope(350,current_field.second_rope_position.y,location_data.current_position.ground_leg_y,location_data.current_position.suspend_leg_y,&obstacle1)
				                        ,100,0,kBothUnStablity,kLocationFirst);
				break;
			}
			else 	if(machineA_general_data.stage_step_number == 6)
			{
			  SetBasicMotionParameters(CrossRope(100,current_field.second_rope_position.y,location_data.current_position.ground_leg_y,location_data.current_position.suspend_leg_y,&obstacle1)
				                        ,100,0,kBothUnStablity,kLocationFirst);
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
				else if(kLegState == kLowLegMove)
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
			leg_angle.initial_yaw = leg_angle.original_yaw;
	    RefreshLegYaw();
			machineA_general_data.plan_isok = false;
		break;
		
	  case kClamber:  
      if(machineA_general_data.stage_step_number == 1)
			{
				leg_state_data.force_time_lay_down_flag = true;
				leg_state_data.force_time_lay_down = 190;
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
			  SetBasicMotionParameters(200,150,0,kClamberSpecialCurve,kClamberWorking);
				break;
			}
			if(machineA_general_data.stage_step_number == 4)
			{
				leg_state_data.leg_state_number_pre = 5;
				SetLegLengthLow(50,50,50,50);
			  SetBasicMotionParameters(200,250,0,kClamberSpecialCurve,kClamberWorking);
				break;
			}
			if(machineA_general_data.stage_step_number == 5)
			{
			  SetBasicMotionParameters(200,300,0,kClamberSpecialCurve,kClamberWorking);
				break;
			}
			if(fabs(leg_angle.original_pitch)<4)
			{
				kMachineAState = kReachSummit;
				machineA_general_data.stage_step_number = 1;
			} 
			else
			{
				SetBasicMotionParameters(200,300,0,kClamberSpecialCurve,kClamberWorking);
				break;
			}
			
	  case kReachSummit: 
			if(machineA_general_data.stage_step_number == 1)
			{
			  SetBasicMotionParameters(100,200,0,kClamberSpecialCurve,kSpeedFirst);
				break;
			}
			else if(machineA_general_data.stage_step_number == 2)
			{
			  SetBasicMotionParameters(100,200,0,kClamberSpecialCurve,kSpeedFirst);
				break;
			}
        leg_state_data.leg_state_number_pre = 6;
			  leg_state_data.leg_state_number = 6;
			  SteadyLegMode();
			  LegModeChange();	
			  LiftToken();
        kMachineAGeneralState = kMachineError;			
			break;
			
		case kRestartPrepareMode:
      if(machineA_general_data.stage_step_number == 1)
			{
			  SetBasicMotionParameters(0,100,0,kBothUnStablity,kRestartPrepare);
				if(kLegState == kHighLegMove)
				{
					DM_MoveInfo.distance_data.target_distance =   field_direction *(Aluminum_Tube_Width/2 + 5)/DM_radio;
				}
				else if(kLegState == kLowLegMove)
				{
					DM_MoveInfo.distance_data.target_distance = - field_direction *(Aluminum_Tube_Width/2 + 5)/DM_radio;
				}
				break;
			}
			kMachineAGeneralState = kWaitToRestart;
			machineA_general_data.stage_step_number = 1;
			break;
		
		default:
			break;
	}
}