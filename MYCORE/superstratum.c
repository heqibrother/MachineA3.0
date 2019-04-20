/*
   To coordinate positioning, planning and control, 
	 regulate and control the operation process, and 
	 encapsulate it into a function
*/
#include "superstratum.h"

MachineAGeneralState kMachineAGeneralState;
MachineAState kMachineAState;
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
	MakePlan();
}

void JudgeMovement()
{
	ExecutePlan();
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