/*
   To coordinate positioning, planning and control, 
	 regulate and control the operation process, and 
	 encapsulate it into a function
*/
#include "superstratum.h"

const float Half_Length = 275.0f;
const float Half_Width = 310.0f;
MachineAGeneralState kMachineAGeneralState;

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