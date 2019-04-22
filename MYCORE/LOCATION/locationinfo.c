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
	  case kBothLegTurnLeft:
	  case kBeforeStepUp:         
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
	ChangePositionRecord(kLegState,&location_data.current_position);
	ChangePositionRecord(kLegState,&location_data.motor_position);
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
		  ChangePositionRecord(kHighLegMove,position);
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
		  ChangePositionRecord(kHighLegMove,position);
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
		  ChangePositionRecord(kHighLegMove,position);
			(*location).ShouldBeTrusted = false;
		}
	}
}

