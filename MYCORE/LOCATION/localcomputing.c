#include "localcomputing.h"
void ChangePositionRecord(LegState klegstate,PositionDataType *position)
{
	if(klegstate==kHighLegMove)
	{
		float highleg_position_x1,highleg_position_x2,highleg_position_x3,
			    highleg_position_y1,highleg_position_y2,highleg_position_y3;
		  highleg_position_x1 = (*position).lowleg_x ;
		  highleg_position_x2= 2*(DriveMotor.PositionMeasure - DM_MoveInfo.position_data.initial_position)* field_direction / DM_radio
		                       * sin(leg_angle.lowleg_yaw*angle_to_radian_radio);//非转动部分造成的x变化
		  highleg_position_x3= (Half_Length - 2*(DriveMotor.PositionMeasure - DM_MoveInfo.position_data.initial_position)* field_direction / DM_radio)
		                        *(sin(leg_angle.lowleg_yaw*angle_to_radian_radio)-sin(leg_angle.highleg_yaw*angle_to_radian_radio));//高腿转动部分造成的x变化
		
		  highleg_position_y1 = (*position).lowleg_y ;
		  highleg_position_y2= +2*(DriveMotor.PositionMeasure - DM_MoveInfo.position_data.initial_position)* field_direction / DM_radio* cos(leg_angle.lowleg_yaw*angle_to_radian_radio);//非转动部分造成的y变化
		  highleg_position_y3= +(Half_Length - 2*(DriveMotor.PositionMeasure - DM_MoveInfo.position_data.initial_position)* field_direction / DM_radio)
		                       *(cos(leg_angle.lowleg_yaw*angle_to_radian_radio)-cos(leg_angle.highleg_yaw*angle_to_radian_radio));//高腿转动部分造成的y变化

				(*position).highleg_x = highleg_position_x1 + field_direction*highleg_position_x2 + field_direction*highleg_position_x3;
	    	(*position).highleg_y = highleg_position_y1 + highleg_position_y2 +highleg_position_y3;

	}
	else if(klegstate == kLowLegMove)
	{
				float lowleg_position_x1,lowleg_position_x2,lowleg_position_x3,
			    lowleg_position_y1,lowleg_position_y2,lowleg_position_y3;
			lowleg_position_x1 = (*position).highleg_x; 
		  lowleg_position_x2= 2*(DriveMotor.PositionMeasure - DM_MoveInfo.position_data.initial_position)* -1 * field_direction / DM_radio
		                      * sin(leg_angle.highleg_yaw*angle_to_radian_radio);//非转动部分造成的x变化
		  lowleg_position_x3= (Half_Length - 2*(DriveMotor.PositionMeasure - DM_MoveInfo.position_data.initial_position)* -1 * field_direction / DM_radio)
		                      *(sin(leg_angle.highleg_yaw*angle_to_radian_radio)-sin(leg_angle.lowleg_yaw*angle_to_radian_radio));//高腿转动部分造成的x变化
		
		  lowleg_position_y1 = (*position).highleg_y ;
		  lowleg_position_y2= +2*(DriveMotor.PositionMeasure - DM_MoveInfo.position_data.initial_position)* -1 * field_direction / DM_radio
		                      * cos(leg_angle.highleg_yaw*angle_to_radian_radio);//非转动部分造成的y变化
		  lowleg_position_y3= +(Half_Length - 2*(DriveMotor.PositionMeasure - DM_MoveInfo.position_data.initial_position)* -1*field_direction / DM_radio)
		                      *(cos(leg_angle.highleg_yaw*angle_to_radian_radio)-cos(leg_angle.lowleg_yaw*angle_to_radian_radio));//高腿转动部分造成的y变化

				(*position).lowleg_x = lowleg_position_x1+ field_direction*lowleg_position_x2 + field_direction*lowleg_position_x3;
		    (*position).lowleg_y = lowleg_position_y1 + lowleg_position_y2 + lowleg_position_y3;

	}
}

float CalOpositionX(float rela_x,float rela_y,int which_turn)//输入以红场正负为标准，
{
	float result_a;
	if(which_turn == kHighLegMove)
	{
		result_a = field_direction * (rela_x*arm_cos_f32(leg_angle.highleg_yaw*angle_to_radian_radio)
		          -rela_y*arm_sin_f32(leg_angle.highleg_yaw*angle_to_radian_radio));
	}
	else
	{
		result_a = field_direction * (rela_x*arm_cos_f32(leg_angle.lowleg_yaw*angle_to_radian_radio)
		          -rela_y*arm_sin_f32(leg_angle.lowleg_yaw*angle_to_radian_radio));
	}
	return result_a;
}

	
float CalOpositionY(float rela_x,float rela_y,int which_turn)
{
		float result_a;
	if(which_turn == kHighLegMove)
	{
		result_a =  (rela_x*arm_sin_f32(leg_angle.highleg_yaw*angle_to_radian_radio)
		            +rela_y*arm_cos_f32(leg_angle.highleg_yaw*angle_to_radian_radio));
	}
	else
	{
		result_a = (rela_x*arm_sin_f32(leg_angle.lowleg_yaw*angle_to_radian_radio)+
		           rela_y*arm_cos_f32(leg_angle.lowleg_yaw*angle_to_radian_radio));
	}

	return result_a;
}
