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
	ReportMessage();
}

void UpdateInformation()
{
	CheckState();
	RefreshLocation();
	RefreshMovementData();
	MakePlan();
}

void JudgeMovement()
{
	if(machineA_general_data.plan_isok &&kMachineAGeneralState == kNormalWalk&& ExecutePlan())
	{
		machineA_general_data.stage_step_number++;
		machineA_general_data.total_step_number++;
		machineA_general_data.plan_isok = false;
		DMStopMove();
		RMStopMove();
		kMachineAGeneralState = kNeedToRestart;
	}
}

void CheckState()
{
	if(!IsDOORTouched(DOOR1))
	{
    kMachineATestItem = kTestFunctionCrossRope;
		kMachineAGeneralState = kNormalWalk;
	}
	if(!IsDOORTouched(DOOR2))
	{

	}
}

void StateInit()
{
	LegPartInit();
	LegYawInit();
	RMPartInit();
	DMPartInit();
	machineA_general_data.plan_isok = false;
	leg_data_feedback.crossed_step = false;
}

void CompetitionInit()
{
	StateInit();
	leg_state_data.leg_state_number = 2;
	leg_state_data.leg_safe_to_laydown =1 ;
	HighlegLift();
	MyDelayms(500);
	kMachineAGeneralState = kWaitToStart;//kWaitDebug;
	kMachineAState = kBeforeStart;
	machineA_general_data.stage_step_number = 1;
	machineA_general_data.total_step_number = 0;
}