#include "locationinfo.h"

void RefreshCurrentPosition()
{
	switch(kMachineAState)
	{
		case kBeforeStart:
    case kStart:            
     // break;			
    case kBeforeLaserDetect: 			
	  case kBeforeTurnLeft:  
		//	GetLaserRadarLocation(&location_data);
       GetLaser1Location(&location_data);			
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
      break;			
		
	  case kBothLegTurnRight:     
	  case kBeforeCrossTheFirstRope:
	  case kCrossTheFirstRope:  
	  case kBeforeCrossTheSecondRope:
	  case kCrossTheSecondRope:
	  case kArriveThePost:          
	  case kStopAtPost:  
			GetRelativeLocation(&location_data);
      break;
		
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
	//(*location).x = field_direction * (*locationdata).relative_data_x - installation.camera_position.x  -field_direction*CalOpositionX(Rplidar_position_X,Rplidar_position_Y,kHighLegMove);
	(*location).y =  (*locationdata).relative_data_y - CalOpositionY(installation.camera_position.x,installation.camera_position.y,kHighLegMove) ; //-field_direction*CalOpositionY(installation.rplidar_position.x,installation.rplidar_position.y,kHighLegMove);
	if(kLegState == kLowLegMove)
	{
		if((*location).ShouldBeTrusted)
		{
			(*position).highleg_y = (*location).y;
			//(*position).highleg_x = (*location).x;
			(*location).ShouldBeTrusted = false;
		}
	}
	else if(kLegState == kHighLegMove)
	{
				if((*location).ShouldBeTrusted)
		{
		  (*position).highleg_y = (*location).y;
		  //(*position).highleg_x =  (*location).x;
		  ChangePositionRecordY(kLowLegMove,position,&DM_MoveInfo);
			(*location).ShouldBeTrusted = false;
		}
	}
}

void GetLaser1Location(LocationData *locationdata)
{
//GetLaserRadarLocation(locationdata);
	LocationDataType *location =&(*locationdata).laser1_position;
	PositionDataType *position =&(*locationdata).current_position;
//	(*location).y = (*locationdata).laser1_data * arm_cos_f32(GetLaseFieldAngle()*angle_to_radian_radio);
//	(*location).y = CalOpositionY(installation.laser_position.x,installation.laser_position.y,kHighLegMove);
//////////////	(*location).y = current_field.hill_position.y - (*locationdata).laser1_data * arm_cos_f32(GetLaseFieldAngle()*angle_to_radian_radio)
//////////////      	-CalOpositionY(installation.laser_position.x,installation.laser_position.y,kHighLegMove);
	//if(fabs(location_data.laser_radar_position.y - (*location).y )<500&&(*locationdata).laser1_data!=0)
	
	//if(kstrategyattribute == kRadicalStrategy)
	{
		(*location).y =current_field.hill_position.y - (*locationdata).laser1_data * arm_cos_f32(GetLaseFieldAngle()*angle_to_radian_radio)
      	-CalOpositionY(installation.laser_position.x,installation.laser_position.y,kHighLegMove) + location_data.laser_correction;
	}
	if((*locationdata).laser1_data > 500&&fabs((*location).y-location_data.motor_position.highleg_y)<1000)
	{
		location_data.laser1_position.ShouldBeTrusted = true;
	}
	else
	{
		location_data.laser1_position.ShouldBeTrusted = false;
	}
		if(kLegState == kLowLegMove)
	{
		if((*location).ShouldBeTrusted)
		{
			(*position).highleg_y = (*location).y;
			//(*position).highleg_x = field_direction * (*location).x;
			(*location).ShouldBeTrusted = false;
		}
	}
	else if(kLegState == kHighLegMove)
	{
				if((*location).ShouldBeTrusted)
		{
		  (*position).highleg_y = (*location).y;
		  //(*position).highleg_x = field_direction * (*location).x;
		  ChangePositionRecordY(kLowLegMove,position,&DM_MoveInfo);
			(*location).ShouldBeTrusted = false;
		}
	}

}

void GetLaserRadarLocation(LocationData *locationdata)
{
	LocationDataType *location =&(*locationdata).laser_radar_position;
	PositionDataType *position =&(*locationdata).current_position;
	(*location).y = current_field.hill_position.y - (*locationdata).laser_radar_data_y -CalOpositionY(installation.rplidar_position.x,installation.rplidar_position.y,kHighLegMove);
	
	if(kLegState == kLowLegMove)
	{
		if((*location).ShouldBeTrusted)
		{
			//(*position).highleg_y = (*location).y;
			(*location).ShouldBeTrusted = false;
		}
	}
	else if(kLegState == kHighLegMove)
	{
				if((*location).ShouldBeTrusted)
		{
		 // (*position).highleg_y = (*location).y;
		 // ChangePositionRecord(kLowLegMove,position,&DM_MoveInfo);
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
                                      			/ FloatSafeDivision(arm_cos_f32((field_direction*45 - leg_angle.highleg_yaw)*angle_to_radian_radio));
			location_data.ground_leg_before_step = 2*Half_Length - location_data.ground_leg_after_step;
			location_data.suspend_leg_before_step = fabs(DriveMotor.PositionMeasure - DM_MoveInfo.position_data.initial_position)*DM_radio * 2
			                                       *arm_cos_f32((field_direction*45 - leg_angle.highleg_yaw)*angle_to_radian_radio);
		}
		else
		{
			location_data.ground_leg_after_step = fabs(DM_MoveInfo.position_data.finish_decelerate_position - DriveMotor.PositionMeasure)*DM_radio * 2 
                                      			/ FloatSafeDivision(arm_cos_f32((field_direction*45 - leg_angle.lowleg_yaw)*angle_to_radian_radio));
			location_data.ground_leg_before_step = 2*Half_Length - location_data.ground_leg_after_step;
			location_data.suspend_leg_before_step = fabs(DriveMotor.PositionMeasure - DM_MoveInfo.position_data.initial_position)*DM_radio * 2
			                                       *arm_cos_f32((field_direction*45 - leg_angle.lowleg_yaw)*angle_to_radian_radio);
		}
	}
}

float GetLaseFieldAngle()
{
	float laser_angle = 0;
	if(field_direction >0)
	  laser_angle = leg_angle.highleg_yaw +  installation.LaserRedAngle;
	else
		laser_angle = leg_angle.highleg_yaw +  installation.LaserBlueAngle;
	
	return laser_angle;
}

