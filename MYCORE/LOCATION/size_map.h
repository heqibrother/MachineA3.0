#ifndef __SIZE_MAP_H
#define __SIZE_MAP_H

#include "location.h"


typedef struct
{
	float x;
	float y;
}PointPosition;

typedef struct
{
	PointPosition initial_position;
	PointPosition first_line_pre_position;
	PointPosition first_line_position;
	PointPosition first_redline_position;
	PointPosition first_line_restart;
	PointPosition second_line_restart;
	PointPosition first_rope_position;
	PointPosition second_rope_position;
	PointPosition second_turn_position;
	PointPosition hill_position;
	
	PointPosition first_redline_test;
	PointPosition second_redline_test;
	
	PointPosition first_column;
	PointPosition second_column;
	PointPosition third_column;
	
	bool para_change_flag;
	bool field_attribute_know_flag;
}FieldPara;

typedef struct
{
	PointPosition camera_position;
	PointPosition rplidar_position;
	PointPosition laser_position;
	PointPosition RedFieldSecondTurnLegCorner;
	PointPosition BlueFieldSecondTurnLegCorner;
	PointPosition SecondRedWhiteLinePoint;
	
	float LaserRedAngle;
  float LaserBlueAngle;
}InstallationLocation;

extern float field_direction ;
extern float which_leg_first_clamber;

extern const float DM_radio ;
extern const float RM_radio ;
extern const float RM_angle_min;
extern const float RM_angle_max;

extern const float Half_Length;
extern const float Half_Width;
extern const float Aluminum_Tube_Width;
extern const float laser_radio;

//extern const float Redline_Position_Prepare ;
//extern const float Initial_Position_Y;
//extern const float Redline_Position_X1;
//extern const float Redline_Position_Y1;
//extern const float Oblique_PositionTurn_X;
//extern const float Rope_Psition_Y1 ;
//extern const float Rope_Psition_Y2 ;
//extern const float Column_Position_X ;
//extern const float Column_Position_Y1 ;
//extern const float Column_Position_Y2 ; 
//extern const float Column_Position_Y3 ; 
//extern const float First_line_restart_X ;
//extern const float First_line_restart_Y ;
//extern const float Second_line_restart_X ;
//extern const float Second_line_restart_Y ;

//extern const float Test_position_Y_to_First_rope ;
//extern const float Hill_Position_Y ;
//extern const float Camera_System_x ; 
//extern const float Camera_System_y ; 

//extern const float Position_Test_X ;
//extern const float Position_Test_Y ;

extern const float Distance_Beyond_Step ;
//extern const float Laser_Position_Y1_Red ;  
//extern const float Laser_Position_Y1_Blue ;

//extern const float Hill_Position_X ;
//extern const float Rplidar_position_X ;
//extern const float Rplidar_position_Y ;
//extern const float Rplidar_diameter ;

//extern const float camera_position_x ;
//extern const float camera_position_y ;

extern FieldPara current_field;
extern InstallationLocation installation;
/*********Function declaration*******/
void FieldParaInit();
void RedFieldParaInit();
void BlueFieldParaInit();
void SetFieldPara(PointPosition *pos,float set_x,float set_y);


#endif