/*
   Responsible for overall planning and dispatching
*/
#include "plan.h"

void MakePlan()
{
	switch(kMachineAGeneralState)
	{
		case kStartingPre:
			StartPreMode();
			break;
		
		case kNormalWalk:
			if(LastWalkOver())
			{
				machineA_general_data.plan_isok = true;
				WalkPlan();
				
			}
			break;
			
		case kClamberModeWaiting:
			LegPrepareForClamber();
			break;
			
		case kNeedToRestart:
			if(JudgeRotateLegsSeparate())
			{
			  if(JudgeLegsSeparate())
			  {
			  Restart();
			  }
		  }
			break;
		
		case kWaitToRestart:
			if(IsDOORTouched(DOOR4))
			{
			 RestartModePlan();
		   kMachineAGeneralState = kNormalWalk;
				handle_command.hRestartCommand = kCommonState;//必须在完成重启初始化后重置
				SendRestartCommandFeedback(kCommonState);
				MyDelayms(20);
			}
			break;
		
		case kWaitCommand:
//			if(LastWalkOver())
		  if(kMachineAState != kClamberReady)
			{
				WalkPlan();
				//machineA_general_data.plan_isok = true;
			}
			if(kMachineAState == kClamberReady&&IsDOORTouched(DOOR4))//用于上坡重启忘了开按钮的事件，开了开关，可以正常上坡重启
			{
				kMachineAGeneralState = kClamberModeWaiting;	
			}
			if(IsDOORTouched(DOOR4)&&kMachineAState <= kStart)
			{
				kMachineAGeneralState = kWaitToStart;
			}
			break;
		
		default:
			break;
	}
}

void SetBasicMotionParameters(float targetpositiondistance,float targetpositionspeed,float targetyaw,SpeedMode speedmode,MovementStyle movementstyle)
{
	DM_MoveInfo.distance_data.target_distance = targetpositiondistance/2.0f;
	DM_MoveInfo.speed_data.target_position_speed = targetpositionspeed;
	leg_angle.target_yaw = targetyaw;
	DM_MoveInfo.speed_data.speed_mode = speedmode;
	movement_style = movementstyle;
	DM_MoveInfo.motor_position = false;
	RM_MoveInfo.motor_position = false;
	RM_speed_stage = kStopMove;
	DM_speed_stage = kStopMove;
	time_point = kBeforeFurtherPlan;
}

bool LastWalkOver()
{
	if(time_point == kAllDone)
	{
		return true;
	}
	if(machineA_general_data.total_step_number==0)
	{
		machineA_general_data.total_step_number=1;
		return true;
	}
	return false;
}

void RestartModePlan()
{
	switch(handle_command.hRestartCommand)
	{
		case kCommonState:
			BeforeStartInitialize();
			break;
		
		case kInitialPositionRestart:
			BeforeStartInitialize();
			break;
		
		case kFirstLinePositionRestart:
			BeforeStepUpInitialize();
			break;
		
		case kSecondLinePositionRestart:
			BeforeTurnRightInitialize();
			break;
		
		case kClamberPositionRestart:
			ClamberModeInitialize();
			break;
		
		case kShowRedFieldTurnLeft:
			ShowRedFieldTurnLeft();
			break;
		
		default:
			break;
	}
}

void Restart()
{
		
	SetCamera(0);
	  machineA_general_data.stage_step_number = 1;
		time_point = kAllDone; 
	  machineA_general_data.plan_isok = false;
	  machineA_general_data.start_time = MyGetTime();
		 if(handle_command.hRestartCommand == kClamberPositionRestart)
		{
					if(which_leg_first_clamber>0)
					{
						kLegState = kHighLegMove;//默认另条腿在上，以便检测到位
					  HighlegLift();
					}
					else
					{
						kLegState = kLowLegMove;
						LowlegLift();
					}
			
			machineA_general_data.stage = kStage4;
			kMachineAGeneralState = kStartingPre;
		}
		else 	if(handle_command.hRestartCommand == kShowRedFieldTurnLeft)
		{
			kLegState = RedFieldLeg(kHighLegMove);//默认另条腿在上，以便检测到位
			RedFieldLegLift(kHighLegMove);
			machineA_general_data.stage = kStage4;
			kMachineAGeneralState = kStartingPre;
			kMachineAState = kMoveRedFieldTurnLeft;
			//kMachineAGeneralState = kMachineError;
		}
		else
		{
//			kstrategyattribute = kConservativeStrategy;
			kLegState = RedFieldLeg(kHighLegMove);//默认另条腿在上，以便检测到位
			RedFieldLegLift(kHighLegMove);
			machineA_general_data.stage = kStage4;
			kMachineAGeneralState = kStartingPre;
			kMachineAState = kRestartPrepareMode;
			//kMachineAGeneralState = kMachineError;

		}
		switch(handle_command.hRestartCommand)
	{
		case kCommonState:
			// leg_state_data.leg_state_number = 2;
	     leg_state_data.leg_state_number_pre = 2;
			break;
		
		case kInitialPositionRestart:
			//leg_state_data.leg_state_number = 2;
	    leg_state_data.leg_state_number_pre = 2;
			break;
		
		case kFirstLinePositionRestart:
			//leg_state_data.leg_state_number = 3;
		  machineA_general_data.hRestartCommandBuf = kFirstLinePositionRestart;
	    leg_state_data.leg_state_number_pre = 3;
			break;
		
		case kSecondLinePositionRestart:
			//leg_state_data.leg_state_number = 7;
	  	machineA_general_data.hRestartCommandBuf = handle_command.hRestartCommand;
	    leg_state_data.leg_state_number_pre = 11;
			break;
		
		case kClamberPositionRestart:
   leg_state_data.leg_state_number_pre = 2;
			kMachineAState = kClamberMode;
//		handle_command.hRestartCommand = kCommonState;
//		SendRestartCommandFeedback(kCommonState);
	//kMachineAGeneralState = kNormalWalk;
	//	handle_command.hRestartCommand = kCommonState;
			break;
		
		case kShowRedFieldTurnLeft:
			leg_state_data.leg_state_number_pre = 3;
			break;
		
		default:
			break;
	}
	 // if(leg_state_data.leg_state_command == 0x1111)

}

void BeforeStartInitialize()
{
	StateRestartInit();
	leg_angle.initial_yaw = leg_angle.original_yaw;
	RefreshLegYaw();
	leg_state_data.leg_state_number = 2;
	leg_state_data.leg_state_number_pre = 2;
	SetLegsInitialPosition(current_field.initial_position.x,current_field.initial_position.y);
	//SetLegsInitialPosition(current_field.initial_position.x,current_field.initial_position.y);
	kMachineAState = kBeforeStart;
	ChangePositionRecord(kLegState,&location_data.current_position,&DM_MoveInfo);
	ChangePositionRecord(kLegState,&location_data.motor_position,&DM_MoveInfo);
	RecordLocation();
	leg_angle.initial_yaw = leg_angle.original_yaw;
}

void BeforeStepUpInitialize()
{
	StateRestartInit();
	leg_angle.initial_yaw = leg_angle.original_yaw - field_direction*45;
	RefreshLegYaw();
	leg_state_data.leg_state_number = 4;
	leg_state_data.leg_state_number_pre = 4;
	SetLegsInitialPosition(current_field.first_line_restart.x,current_field.first_line_restart.y);
	kMachineAState = kBeforeStepUp;
	ChangePositionRecord(kLegState,&location_data.current_position,&DM_MoveInfo);
	ChangePositionRecord(kLegState,&location_data.motor_position,&DM_MoveInfo);
	RecordLocation();

}

void BeforeTurnRightInitialize()
{
	StateRestartInit();
	leg_angle.initial_yaw = leg_angle.original_yaw - field_direction*45;
	RefreshLegYaw();
	leg_state_data.leg_state_number = 11;
	leg_state_data.leg_state_number_pre = 11;
	if(field_direction>0)
	{
			current_field.second_line_restart.y = current_field.first_rope_position.y + installation.SecondRedWhiteLinePoint.y 
	          - CalOpositionY(installation.RedFieldSecondTurnLegCorner.x,installation.RedFieldSecondTurnLegCorner.y,kLowLegMove);
	}
	else
	{
			current_field.second_line_restart.y = current_field.first_rope_position.y + installation.SecondRedWhiteLinePoint.y 
	          - CalOpositionY(installation.BlueFieldSecondTurnLegCorner.x,installation.BlueFieldSecondTurnLegCorner.y,kHighLegMove);
	}

	SetLegsInitialPosition(current_field.second_line_restart.x,current_field.second_line_restart.y);
	kMachineAState = kBeforeTurnRight;
	ChangePositionRecord(kLegState,&location_data.current_position,&DM_MoveInfo);
	ChangePositionRecord(kLegState,&location_data.motor_position,&DM_MoveInfo);
	RecordLocation();

}

void ClamberModeInitialize()
{
	  StateRestartInit();		
	leg_angle.initial_yaw = leg_angle.original_yaw ;
    kMachineAState = kClamberReady;
	 kMachineAGeneralState = kClamberModeWaiting;	
		machineA_general_data.stage_step_number = 1;
//- field_direction*45;
	  RefreshLegYaw();
}

void ShowRedFieldTurnLeft()
{
	
}
//void SettingObstacleCrossingParameters(bool )
//{
//	
//}