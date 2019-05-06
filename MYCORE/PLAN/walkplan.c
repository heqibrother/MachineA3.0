#include "walkplan.h"
StrategyAttribute kstrategyattribute;

void WalkPlan()
{
//	switch(kstrategyattribute)
//	{
//		case kRadicalStrategy:
//			FastWalkPlan();
//			break;
//		
//		case kNeutralStrategy:
//			NormalWalkPlan();
//		break;
//	
//		case kConservativeStrategy:
//			SlowWalkPlan();
//		break;
//		
//		default:
//			break;
//	}
	
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
				  ,300,0,kBothUnStablity,kSpeedFirst);   
				 break;
			 }				 
			  if(kstrategyattribute == kNeutralStrategy)kMachineAGeneralState = kMachineError;
			 	kMachineAState = kTurnLeft;
				machineA_general_data.stage_step_number = 1;
			 
	  case kTurnLeft:  
		   leg_state_data.leg_state_number_pre = 3;
        if(machineA_general_data.stage_step_number == 1)
			{
			  SetBasicMotionParameters(160,120,45*field_direction,kBothUnStablity,kRisingTurn);
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
				SetBasicMotionParameters(300,150,45*field_direction,kBothStability,kDetectStep);
				break;
			}
			kMachineAState = kStepUp;
			machineA_general_data.stage_step_number = 1;
			
	  case kStepUp:
     		if(machineA_general_data.stage_step_number == 1)
			{
			  SetBasicMotionParameters(Distance_Beyond_Step - location_data.ground_leg_after_step,150,45*field_direction,kBothStability,kCrossStep);
				SetObstacleLocation(location_data.suspend_leg_before_step,0,&obstacle1);
				location_data.suspend_leg_before_step = 2*Half_Length - Distance_Beyond_Step;
				break;
			}
			  kMachineAState = kClimbOverTheStep;
				machineA_general_data.stage_step_number = 1;
		
	  case kClimbOverTheStep:  
      if(machineA_general_data.stage_step_number == 1)
			{
			  SetBasicMotionParameters(300,200,45*field_direction,kBothStability,kCrossStep);
				SetObstacleLocation(location_data.ground_leg_before_step,300,&obstacle1);
				location_data.ground_leg_after_step = location_data.suspend_leg_before_step - 300;

				break;
			}			
			if(machineA_general_data.stage_step_number == 2)
			{
			  SetBasicMotionParameters(250,200,60*field_direction,kBothStability,kCrossedStep);
				SetObstacleLocation(location_data.suspend_leg_before_step,300,&obstacle1);
				break;
			}
			if(machineA_general_data.stage_step_number == 3)
			{
				leg_state_data.leg_state_number_pre = 11;
			  SetBasicMotionParameters(250,200,60*field_direction,kFlexibleSteady,kCrossedStep);
				SetObstacleLocation(location_data.ground_leg_after_step,300,&obstacle1);
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
			                                             280*arm_sin_f32(60*angle_to_radian_radio),RedFieldLeg(kHighLegMove),&machineA_general_data.step_number_left,70.0f*arm_sin_f32(60*angle_to_radian_radio))
			                                          /arm_sin_f32(60*angle_to_radian_radio);
     if(machineA_general_data.step_number_left!=0)
		 {
			   SetBasicMotionParameters(machineA_general_data.target_distance
				  ,200,60*field_direction,kFlexibleSteady,kSpeedFirst);   

			 if(machineA_general_data.hRestartCommandBuf == kSecondLinePositionRestart)
			 {
				 				 SetBasicMotionParameters(machineA_general_data.target_distance
				  ,100,60*field_direction,kFlexibleSteady,kSpeedFirst); 
			 }
        else	if(kstrategyattribute == kConservativeStrategy)
			 {
				 			   SetBasicMotionParameters(machineA_general_data.target_distance
				  ,100,60*field_direction,kFlexibleSteady,kSpeedFirst); 
			 }
				 break;
		 }
		 kMachineAState = kTurnRight;
		// kMachineAGeneralState = kMachineError;
		 machineA_general_data.stage_step_number = 1;
		
	  case kTurnRight:
      SetCamera(0);
     	if(machineA_general_data.stage_step_number == 1)
			{
			  SetBasicMotionParameters(160,80,0,kFlexibleSteady,kLocationFirst);
				if(machineA_general_data.hRestartCommandBuf == kSecondLinePositionRestart)
				{
					SetBasicMotionParameters(160,50,0,kFlexibleSteady,kLocationFirst);
				}
				else
					 if(kstrategyattribute == kConservativeStrategy)
					 {
						   SetBasicMotionParameters(160,50,0,kFlexibleSteady,kLocationFirst);
					 }
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
					if(machineA_general_data.hRestartCommandBuf == kSecondLinePositionRestart)
				{
					  SetBasicMotionParameters(100,50,0,kFlexibleSteady,kRisingTurn);
					machineA_general_data.hRestartCommandBuf = kCommonState;
				}
				else
						if(kstrategyattribute == kConservativeStrategy)
					 {
						   SetBasicMotionParameters(100,50,0,kFlexibleSteady,kRisingTurn);
					 }
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
				                        ,150,0,kBothUnStablity,kLocationFirst);
				break;
			}
			else 	if(machineA_general_data.stage_step_number == 5)
			{
			  SetBasicMotionParameters(CrossRope(350,current_field.second_rope_position.y,location_data.current_position.ground_leg_y,location_data.current_position.suspend_leg_y,&obstacle1)
				                        ,150,0,kBothUnStablity,kLocationFirst);
				break;
			}
			else 	if(machineA_general_data.stage_step_number == 6)
			{
			  SetBasicMotionParameters(CrossRope(100,current_field.second_rope_position.y,location_data.current_position.ground_leg_y,location_data.current_position.suspend_leg_y,&obstacle1)
				                        ,150,0,kBothUnStablity,kEndWalk);
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
					DM_MoveInfo.distance_data.target_distance = which_leg_first_clamber*(Aluminum_Tube_Width/2 + 15);
				}
				else if(kLegState == kLowLegMove)
				{
					DM_MoveInfo.distance_data.target_distance = -1*which_leg_first_clamber*(Aluminum_Tube_Width/2 + 15);
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
			handle_command.hRestartCommand = kCommonState;
  		SendRestartCommandFeedback(kCommonState);
			machineA_general_data.plan_isok = false;
		break;
		
	  case kClamber:  
			if(kstrategyattribute == kRadicalStrategy)
			{
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
			  SetBasicMotionParameters(300,175,0,kClamberSpecialCurve,kClamberWorking);
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
			  SetBasicMotionParameters(225,250,0,kClamberSpecialCurve,kClamberWorking);
				break;
			}
			if(machineA_general_data.stage_step_number == 5)
			{
			  SetBasicMotionParameters(250,350,0,kClamberSpecialCurve,kClamberWorking);
				break;
			}
			if(fabs(leg_angle.original_pitch)<4)
			{
				kMachineAState = kReachSummit;
				machineA_general_data.stage_step_number = 1;
			} 
			else
			{
				SetBasicMotionParameters(250,350,0,kClamberSpecialCurve,kClamberWorking);
				break;
			}
		}
			else if(kstrategyattribute == kConservativeStrategy)
			{
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
						leg_state_data.force_time_lay_down_flag = true;
						leg_state_data.force_time_lay_down = 120;
						SetLegLengthLow(80,80,80,50);
						SetBasicMotionParameters(200,150,0,kClamberSpecialCurve,kClamberWorking);
						break;
					}			
					if(machineA_general_data.stage_step_number == 3)
					{
						SetLegLengthLow(80,60,60,80);
						SetBasicMotionParameters(200,150,0,kOnlyAccelerateStability,kClamberWorking);
						break;
					}
					if(machineA_general_data.stage_step_number == 4)
					{
						leg_state_data.leg_state_number_pre = 5;
						SetLegLengthLow(50,50,50,50);
						SetBasicMotionParameters(225,150,0,kClamberSpecialCurve,kClamberWorking);
						break;
					}
					if(machineA_general_data.stage_step_number == 5)
					{
						SetBasicMotionParameters(250,150,0,kClamberSpecialCurve,kClamberWorking);
						break;
					}
					if(fabs(leg_angle.original_pitch)<4)
					{
						kMachineAState = kReachSummit;
						machineA_general_data.stage_step_number = 1;
					} 
					else
					{
						SetBasicMotionParameters(250,150,0,kClamberSpecialCurve,kClamberWorking);
						break;
					}
			}
			else
			{
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
						SetBasicMotionParameters(300,175,0,kClamberSpecialCurve,kClamberWorking);
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
						SetBasicMotionParameters(225,250,0,kClamberSpecialCurve,kClamberWorking);
						break;
					}
					if(machineA_general_data.stage_step_number == 5)
					{
						SetBasicMotionParameters(250,350,0,kClamberSpecialCurve,kClamberWorking);
						break;
					}
					if(fabs(leg_angle.original_pitch)<4)
					{
						kMachineAState = kReachSummit;
						machineA_general_data.stage_step_number = 1;
					} 
					else
					{
						SetBasicMotionParameters(250,350,0,kClamberSpecialCurve,kClamberWorking);
						break;
					}
			}
			
	  case kReachSummit: 
			if(machineA_general_data.stage_step_number == 1)
			{
			  SetBasicMotionParameters(150,200,0,kClamberSpecialCurve,kSpeedFirst);
				break;
			}
			else if(machineA_general_data.stage_step_number == 2)
			{
			  SetBasicMotionParameters(100,100,0,kClamberSpecialCurve,kSpeedFirst);
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
					if(kLegState == RedFieldLeg(kHighLegMove))
				{
					DM_MoveInfo.distance_data.target_distance = (Aluminum_Tube_Width/2 + 15);
				}
				else if(kLegState == RedFieldLeg(kLowLegMove))
				{
					DM_MoveInfo.distance_data.target_distance = -(Aluminum_Tube_Width/2 + 15);
				}
				break;
			}
			kMachineAGeneralState = kWaitToRestart;
			machineA_general_data.stage_step_number = 1;
			break;
			
		case kMoveRedFieldTurnLeft: 
			  if(machineA_general_data.stage_step_number == 1)
			{
			  SetBasicMotionParameters(160,120,45*field_direction,kBothUnStablity,kShowTurn);
				break;
			}
			  kMachineAGeneralState = kWaitToRestart;
			  kLegState = RedFieldLeg(kHighLegMove);
				SetSpeedDirection();
			 // kMachineAState = kWaitToRestart;
				machineA_general_data.stage_step_number = 1;
			break;
		
		default:
			break;
	}

}