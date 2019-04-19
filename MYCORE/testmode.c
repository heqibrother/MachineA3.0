#include "testmode.h"

MachineATestItem kMachineATestItem;
float test_value1[4] = {0};
int test_value[4] = {0};

void TestInit()
{
	test_value1[0] = 200;
	test_value1[1] = 20;
	test_value1[2] = 0;
	SetBasicMotionParameters(test_value1[0],test_value1[1],test_value1[2],0);
	MotorOff(CAN2);
	StateInit();
	leg_state_data.leg_state_number = 2;
	HighlegLift();
	kMachineATestItem = kWaitDebug;
}

void TestMode()
{
	switch(kMachineATestItem)
	{
		case kWaitDebug:
			
			break;
		
		case kTestVelocityCurveWithoutChangeLeg:
		  if(ExecutePlan())
			{
				SetBasicMotionParameters(test_value1[0],test_value1[1],test_value1[2],0);
			}
			break;
	}
}