/*
   To coordinate positioning, planning and control, 
	 regulate and control the operation process, and 
	 encapsulate it into a function
*/
#include "superstratum.h"

MachineAGeneralState kMachineAGeneralState;
MachineAState kMachineAState;
MachineAGeneralData machineA_general_data;
void CompetitionMode()
{
	UpdateInformation();
	JudgeMovement();
	//ReportMessage();
}

void UpdateInformation()
{
	RefreshLocation();
	RefreshMovementData();
	MakePlan();
	CheckState();
}

void JudgeMovement()
{
	if(machineA_general_data.plan_isok &&kMachineAGeneralState == kNormalWalk&& ExecutePlan())
	{
		machineA_general_data.stage_step_number++;
		machineA_general_data.total_step_number++;
		machineA_general_data.plan_isok = false;
//		DMStopMove();//
//		RMStopMove();
//		kMachineAGeneralState = kWaitCommand;
	}
}

void CheckState()
{
	if(!IsDOORTouched(DOOR1))
	{
		kMachineAGeneralState = kNormalWalk;
 //    if(kMachineAState == kArriveThePost)
		 {
//			 machineA_general_data.plan_isok = false;
//	     DMStopMove();
//		   RMStopMove();
//			 time_point = kAllDone;
//			 kMachineAState = kClamberMode;
//			 kLegState =  DetectLegState();
//			 if(kLegState == kAnyLegMove)kMachineAGeneralState = kMachineError;
//			 machineA_general_data.stage_step_number = 1;
		 }
	}
	if(!IsDOORTouched(DOOR2))
	{
		if(kMachineAGeneralState == kWaitToStart&&kMachineAGeneralState != kStartingPre)
		{			
			machineA_general_data.stage = kStage1;
      kMachineATestItem = kTestFunctionCrossRope;
		  kMachineAGeneralState = kStartingPre;
		}
	}

	if(!IsDOORTouched(DOOR3))
	{
		if(kMachineAGeneralState == kClamberModeWaiting&&kMachineAState == kClamberReady)
		{
			kMachineAGeneralState = kNormalWalk;
			kMachineAState = kClamber;
			leg_angle.initial_yaw = leg_angle.original_yaw;
	    RefreshLegYaw();
			time_point = kAllDone; 
			
		}
	}
	
	if(!IsDOORTouched(DOOR4)
		&&(kMachineAGeneralState != kWaitToRestart&&kMachineAGeneralState != kNeedToRestart)
	&&(handle_command.hRestartCommand == kCommonState))//&&handle_command.hRestartCommand != kCommonState)
	{
		DMStopMove();
		RMStopMove();
		kMachineAGeneralState = kWaitCommand;
		//kMachineAGeneralState = kMachineError;
	}
}

void StateInit()
{
  //MotorOff(CAN2);
	FieldParaInit();
	OrgansInit();
	LegPartInit();
	LegYawInit();
	RMPartInit();
	DMPartInit();
	PositionInit();
	OrgansInit();
	machineA_general_data.plan_isok = false;
	leg_data_feedback.crossed_step = false;
	leg_data_feedback.send_leg_change_flag = false;
	leg_state_data.leg_safe_to_laydown =1 ;
}

void CompetitionInit()
{
	StateInit();
	kMachineAGeneralState = kWaitToStart;//kWaitDebug;
//	TestFirstRedLine();
//	TestSecondRedLine();
	FormalStart();
//	TestClamberMode();
	machineA_general_data.stage_step_number = 1;
	machineA_general_data.total_step_number = 0;
}

void FormalStart()
{
	leg_state_data.leg_state_number = 1;
	SteadyLegMode();
	SetLegsInitialPosition(current_field.initial_position.x,current_field.initial_position.y);
	kMachineAState = kBeforeStart;
	leg_state_data.leg_state_number_pre = 2;
	ChangePositionRecord(kLegState,&location_data.current_position,&DM_MoveInfo);
	ChangePositionRecord(kLegState,&location_data.motor_position,&DM_MoveInfo);
	RecordLocation();
	leg_angle.initial_yaw = leg_angle.original_yaw;
	RefreshLegYaw();
}

void StartPreMode()
{
	switch(machineA_general_data.stage)
	{
		case kStage1:
		 leg_state_data.leg_state_number = 2;
	   SteadyLegMode();
		 machineA_general_data.start_time = MyGetTime();
		 machineA_general_data.stage = kStage2;
		
		case kStage2:
			if(MyGetTime() - machineA_general_data.start_time>200)
			{
				TakeToken();
				machineA_general_data.stage = kStage3;
				machineA_general_data.start_time = MyGetTime();
			}
			else break;
				
		case kStage3:
			if(MyGetTime() - machineA_general_data.start_time>200)
			{
				machineA_general_data.stage = kStage4;
				kLegState = RedFieldLeg(kHighLegMove);
				RedFieldLegLift(kHighLegMove);
				machineA_general_data.start_time = MyGetTime();
			}
			else break;
		
		case kStage4:
		if(DetectLegRecoverPosition()&&MyGetTime() - machineA_general_data.start_time>50)
		{
				//kLegState = RedFieldLeg(kHighLegMove);
		  machineA_general_data.stage = kStage5;
			kMachineAGeneralState = kNormalWalk;
			machineA_general_data.stage_step_number = 1;//非常重要，保证中间没有累加
		}
			break;
		
		default:
			break;
	}
}