#include "testmode.h"

MachineATestItem kMachineATestItem;
float test_value1[4] = {0};
float test_value[4] = {0};
float show_data[4] = {0.0f};

void TestInit()
{

	MotorOff(CAN2);
	StateInit();
	leg_state_data.leg_state_number = 2;
	HighlegLift();
	MyDelayms(1000);
	test_value[0] = 370;
	test_value[1] = 1000;
	test_value[2] = 900;
	test_value[3] = 800;
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
			
		case kTestStepDistanceCal:
				if(ExecutePlan())
			{
				 if(location_data.current_position.ground_leg_y<1000-50)
			 {
         SetBasicMotionParameters(CalStepDistance(1000,location_data.current_position.ground_leg_y,300,kLowLegMove)
				  ,100,0,kBothUnStablity,kSpeedFirst);   
			 }
				kMachineATestItem = kWaitDebug;
			}
			VisualScope_Send(DM_MoveInfo.distance_data.target_distance,
								 CalStepDistance(1000,location_data.current_position.ground_leg_y,300,kLowLegMove),
								 location_data.current_position.highleg_y,
								 location_data.current_position.lowleg_y);
			break;
			
		case kTestFunctionCalStepDistance:
			//test_value[0] = 1000;
			show_data[0] = CalStepDistance(test_value[0],location_data.current_position.ground_leg_y,300,kLowLegMove);
		  kMachineATestItem = kWaitDebug;
			break;
		
		case kTestFunctionCrossRope:
			//float CrossRope(float distance_hope,float rope_position,float ground_leg_position,float suspend_leg_position)
			//test_value[0] = 370;
			//test_value[1] = 1000;
			//test_value[2] = 900;
			//test_value[3] = 800;
			show_data[0] = CrossRope(test_value[0],test_value[1],test_value[2],test_value[3],&obstacle1);
		  kMachineATestItem = kWaitDebug;
			break;
		
		default:
			break;
	}
}

void TestFirstRedLine()
{
	location_data.current_position.lowleg_x = Redline_Position_X1;
	location_data.current_position.lowleg_y = Redline_Position_Y1;
	kMachineAState = kTurnLeft;
	ChangePositionRecord(kLegState,&location_data.current_position,&DM_MoveInfo);
	ChangePositionRecord(kLegState,&location_data.motor_position,&DM_MoveInfo);
	RecordLocation();
	leg_angle.initial_yaw = leg_angle.original_yaw ;//- 45*field_direction;
	RefreshLegYaw();
}

void TestSecondRedLine()
{
	location_data.current_position.lowleg_x = Second_line_restart_X;
	location_data.current_position.lowleg_y = Second_line_restart_Y;
	kMachineAState = kBeforeTurnRight;
	leg_state_data.leg_state_number_pre = 7;
	ChangePositionRecord(kLegState,&location_data.current_position,&DM_MoveInfo);
	ChangePositionRecord(kLegState,&location_data.motor_position,&DM_MoveInfo);
	RecordLocation();
	leg_angle.initial_yaw = leg_angle.original_yaw - 45*field_direction;
	RefreshLegYaw();
}