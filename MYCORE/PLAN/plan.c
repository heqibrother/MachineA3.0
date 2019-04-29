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
				WalkPlan();
				machineA_general_data.plan_isok = true;
			}
			break;
			
		case kClamberModeWaiting:
			LegPrepareForClamber();
			break;
			
		case kNeedToRestart:
			Restart();
			break;
		
		case kWaitToRestart:
			if(IsDOORTouched(DOOR4))
			{
				
			 RestartModePlan();
		   kMachineAGeneralState = kNormalWalk;
				handle_command.hRestartCommand = kCommonState;//必须在完成重启初始化后重置
				MyDelayms(20);
			}
			break;
		
		case kWaitCommand:
//			if(LastWalkOver())
			{
				WalkPlan();
				machineA_general_data.plan_isok = true;
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
		
		default:
			break;
	}
}

void Restart()
{
		
		kMachineAState = kRestartPrepareMode;
	  machineA_general_data.stage_step_number = 1;
		time_point = kAllDone; 
	  machineA_general_data.plan_isok = false;
	  machineA_general_data.start_time = MyGetTime();
		 if(handle_command.hRestartCommand != kClamberPositionRestart)
		{
			kLegState = RedFieldLeg(kHighLegMove);//默认另条腿在上，以便检测到位
			RedFieldLegLift(kHighLegMove);
			machineA_general_data.stage = kStage4;
			kMachineAGeneralState = kStartingPre;
		}
		else
		{
			kLegState = kHighLegMove;//默认另条腿在上，以便检测到位
		  HighlegLift();
			machineA_general_data.stage = kStage4;
			kMachineAGeneralState = kStartingPre;
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
	    leg_state_data.leg_state_number_pre = 3;
			break;
		
		case kSecondLinePositionRestart:
			//leg_state_data.leg_state_number = 7;
	    leg_state_data.leg_state_number_pre = 7;
			break;
		
		case kClamberPositionRestart:
   leg_state_data.leg_state_number_pre = 2;
			kMachineAState = kClamberMode;
	//kMachineAGeneralState = kNormalWalk;
	//	handle_command.hRestartCommand = kCommonState;
			break;
		
		default:
			break;
	}
	 // if(leg_state_data.leg_state_command == 0x1111)

}

void BeforeStartInitialize()
{
	StateInit();
	leg_state_data.leg_state_number = 2;
	leg_state_data.leg_state_number_pre = 2;
	SetLegsInitialPosition(current_field.initial_position.x,current_field.initial_position.y);
	kMachineAState = kBeforeStart;
	ChangePositionRecord(kLegState,&location_data.current_position,&DM_MoveInfo);
	ChangePositionRecord(kLegState,&location_data.motor_position,&DM_MoveInfo);
	RecordLocation();
	leg_angle.initial_yaw = leg_angle.original_yaw;
	RefreshLegYaw();
}

void BeforeStepUpInitialize()
{
	StateInit();
	leg_state_data.leg_state_number = 3;
	leg_state_data.leg_state_number_pre = 4;
	SetLegsInitialPosition(current_field.first_line_restart.x,current_field.first_line_restart.y);
	kMachineAState = kBeforeStepUp;
	ChangePositionRecord(kLegState,&location_data.current_position,&DM_MoveInfo);
	ChangePositionRecord(kLegState,&location_data.motor_position,&DM_MoveInfo);
	RecordLocation();
	leg_angle.initial_yaw = leg_angle.original_yaw - field_direction*45;
	RefreshLegYaw();
}

void BeforeTurnRightInitialize()
{
	StateInit();
	leg_state_data.leg_state_number = 7;
	leg_state_data.leg_state_number_pre = 7;
	SetLegsInitialPosition(current_field.second_line_restart.x,current_field.second_line_restart.y);
	kMachineAState = kBeforeTurnRight;
	ChangePositionRecord(kLegState,&location_data.current_position,&DM_MoveInfo);
	ChangePositionRecord(kLegState,&location_data.motor_position,&DM_MoveInfo);
	RecordLocation();
	leg_angle.initial_yaw = leg_angle.original_yaw - field_direction*45;
	RefreshLegYaw();
}

void ClamberModeInitialize()
{
	  StateInit();
    kMachineAState = kClamberReady;
	 kMachineAGeneralState = kClamberModeWaiting;	
		machineA_general_data.stage_step_number = 1;
		leg_angle.initial_yaw = leg_angle.original_yaw ;//- field_direction*45;
	  RefreshLegYaw();
}
//void SettingObstacleCrossingParameters(bool )
//{
//	
//}