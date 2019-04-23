#include "locationinfo.h"

void RefreshCurrentPosition()
{
	switch(kMachineAState)
	{
		case kBeforeStart:
    case kStart:               
    case kBeforeLaserDetect:   
	  case kBeforeTurnLeft:      
	  case kTurnLeft:   
       break;			
		
	  case kBothLegTurnLeft:
	  case kBeforeStepUp:    
       GetStepLocationData();
      break;
		
	  case kStepUp:             
	  case kClimbOverTheStep:      
	  case kBeforeTurnRight:      
	  case kTurnRight:       
	  case kBothLegTurnRight:     
	  case kBeforeCrossTheFirstRope:
	  case kCrossTheFirstRope:  
	  case kBeforeCrossTheSecondRope:
	  case kCrossTheSecondRope:
	  case kArriveThePost:          
	  case kStopAtPost:           
		default:
			break;
	}
	ChangePositionRecord(kLegState,&location_data.current_position,&DM_MoveInfo);
	ChangePositionRecord(kLegState,&location_data.motor_position,&DM_MoveInfo);
	RecordLocation();
}

void GetRelativeLocation(LocationData *locationdata)
{
	LocationDataType *location =&(*locationdata).relative_position;
	PositionDataType *position =&(*locationdata).current_position;
	(*location).x = field_direction * (*locationdata).relative_data_x - Camera_System_x  -field_direction*CalOpositionX(Rplidar_position_X,Rplidar_position_Y,kHighLegMove);
	(*location).y =  (*locationdata).relative_data_y - Camera_System_y  -field_direction*CalOpositionY(Rplidar_position_X,Rplidar_position_Y,kHighLegMove);
	if(kLegState == kHighLegMove)
	{
		if((*location).ShouldBeTrusted)
		{
			(*position).highleg_y = (*location).y;
			(*position).highleg_x = (*location).x;
			(*location).ShouldBeTrusted = false;
		}
	}
	else if(kLegState == kLowLegMove)
	{
				if((*location).ShouldBeTrusted)
		{
		  (*position).highleg_y = (*location).y;
		  (*position).highleg_x =  (*location).x;
		  ChangePositionRecord(kHighLegMove,position,&DM_MoveInfo);
			(*location).ShouldBeTrusted = false;
		}
	}
}

void GetLaser1Location(LocationData *locationdata)
{
	GetLaserRadarLocation(locationdata);
	LocationDataType *location =&(*locationdata).laser1_position;
	PositionDataType *position =&(*locationdata).current_position;
	(*location).y = Hill_Position_Y - (*locationdata).laser1_data -CalOpositionY(Rplidar_position_X,Rplidar_position_Y,kHighLegMove);
	if(kLegState == kHighLegMove)
	{
		if((*location).ShouldBeTrusted)
		{
			(*position).highleg_y = (*location).y;
			(*position).highleg_x = field_direction * (*location).x;
			(*location).ShouldBeTrusted = false;
		}
	}
	else if(kLegState == kLowLegMove)
	{
				if((*location).ShouldBeTrusted)
		{
		  (*position).highleg_y = (*location).y;
		  (*position).highleg_x = field_direction * (*location).x;
		  ChangePositionRecord(kHighLegMove,position,&DM_MoveInfo);
			(*location).ShouldBeTrusted = false;
		}
	}
}

void GetLaserRadarLocation(LocationData *locationdata)
{
	LocationDataType *location =&(*locationdata).laser_radar_position;
	PositionDataType *position =&(*locationdata).current_position;
	(*location).y = Hill_Position_Y - (*locationdata).laser_radar_data_y -CalOpositionY(Rplidar_position_X,Rplidar_position_Y,kHighLegMove);
	if(kLegState == kHighLegMove)
	{
		if((*location).ShouldBeTrusted)
		{
			(*position).highleg_y = (*location).y;
			(*location).ShouldBeTrusted = false;
		}
	}
	else if(kLegState == kLowLegMove)
	{
				if((*location).ShouldBeTrusted)
		{
		  (*position).highleg_y = (*location).y;
		  ChangePositionRecord(kHighLegMove,position,&DM_MoveInfo);
			(*location).ShouldBeTrusted = false;
		}
	}
}

void GetStepLocationData()
{
	if(leg_data_feedback.crossd_step_state==1&&!leg_data_feedback.crossed_step)
	{
		leg_data_feedback.crossed_step = true;
		if(kLegState == kHighLegMove)
		{
			location_data.ground_leg_after_step = fabs(DM_MoveInfo.position_data.finish_decelerate_position - DriveMotor.PositionMeasure)*DM_radio * 2 
                                      			/ arm_cos_f32((45 - leg_angle.highleg_yaw)*angle_to_radian_radio);
			location_data.ground_leg_before_step = 2*Half_Length - location_data.ground_leg_after_step;
			location_data.suspend_leg_before_step = fabs(DriveMotor.PositionMeasure - DM_MoveInfo.position_data.initial_position)*DM_radio * 2
			                                       *arm_cos_f32((45 - leg_angle.highleg_yaw)*angle_to_radian_radio);
		}
		else
		{
			location_data.ground_leg_after_step = fabs(DM_MoveInfo.position_data.finish_decelerate_position - DriveMotor.PositionMeasure)*DM_radio * 2 
                                      			/ arm_cos_f32((45 - leg_angle.lowleg_yaw)*angle_to_radian_radio);
			location_data.ground_leg_before_step = 2*Half_Length - location_data.ground_leg_after_step;
			location_data.suspend_leg_before_step = fabs(DriveMotor.PositionMeasure - DM_MoveInfo.position_data.initial_position)*DM_radio * 2
			                                       *arm_cos_f32((45 - leg_angle.lowleg_yaw)*angle_to_radian_radio);
		}
		

		
	}
}

