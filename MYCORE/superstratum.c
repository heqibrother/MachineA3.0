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
	if(ExecutePlan())
	{
		machineA_general_data.stage_step_number++;
		machineA_general_data.total_step_number++;
	}
}

void CheckState()
{
	
}

void StateInit()
{
	LegPartInit();
	LegYawInit();
	RMPartInit();
	DMPartInit();
}

void CompetitionInit()
{
	StateInit();
	leg_state_data.leg_state_number = 2;
	leg_state_data.leg_safe_to_laydown =1 ;
	HighlegLift();
	MyDelayms(500);
	kMachineAGeneralState = kNormalWalk;//kWaitDebug;
	kMachineAState = kBeforeStart;
	machineA_general_data.stage_step_number = 1;
	machineA_general_data.total_step_number = 0;
}