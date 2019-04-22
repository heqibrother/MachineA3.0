#include "testmode.h"

MachineATestItem kMachineATestItem;
float test_value1[4] = {0};
int test_value[4] = {0};

void TestInit()
{

//	MotorOff(CAN2);
	StateInit();
	leg_state_data.leg_state_number = 2;
	HighlegLift();
	MyDelayms(1000);
	kMachineATestItem = kWaitDebug;
	test_value1[0] = 300;
	test_value1[1] = 100;
	test_value1[2] = kBothUnStablity;
	SetBasicMotionParameters(test_value1[0],test_value1[1],test_value1[2],0,kSpeedFirst);
}

void TestMode()
{
	 CheckState();
	 RefreshLocation();
	 RefreshMovementData();
	switch(kMachineATestItem)
	{
		case kWaitDebug:
		//	SetBasicMotionParameters(test_value1[0],test_value1[1],test_value1[2],0);
			break;
		
		case kTestVelocityCurveWithoutChangeLeg:
		  if(ExecutePlan())
			{
				SetBasicMotionParameters(test_value1[0],test_value1[1],test_value1[2],0,kSpeedFirst);
				//kMachineATestItem = kWaitDebug;
			}
			break;
			
		case kTestMotorLocation:
			if(ExecutePlan())
			{
				SetBasicMotionParameters(test_value1[0],test_value1[1],test_value1[2],0,kSpeedFirst);
				kMachineATestItem = kWaitDebug;
			}
			VisualScope_Send(location_data.current_position.ground_leg_y,
			                 location_data.current_position.suspend_leg_y,
			                 location_data.current_position.highleg_y,
			                 location_data.current_position.lowleg_y);
			break;
		
		default:
			break;
	}
}