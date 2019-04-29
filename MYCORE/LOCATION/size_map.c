#include "size_map.h"

FieldPara current_field;
InstallationLocation installation;
const float field_direction = +1.0f;

const float DM_radio = 0.57596f;//   66pi（3.141592654）/360  //motor_angle * radio = real distance
const float RM_radio = 0.265625f;//0.32075f;//34:128 //motor_angle * radio = real angle
const float RM_angle_min = 3.0f;
const float RM_angle_max = 70.0f;

const float Half_Length = 275.0f;//275.0f;
const float Half_Width = 310.0f;
const float Aluminum_Tube_Width = 25.0f;
const float laser_radio = 1.625;  //6.5:4

	 
	 /*相对定位坐标系*/
const float Redline_Position_Prepare =1480.0f;//开始准备转向的位置（开始调整步距）
const float Initial_Position_Y= 25.0f;
const float Redline_Position_X1= -510.0f;///-630////-950//-510 //第一次转向位置X
const float Redline_Position_Y1 =3160.0f;//1000//3160//3950 //第一次转向位置Y
const float Oblique_PositionTurn_X= 950.0f;//第二次转向位置X
const float Rope_Psition_Y1 =5050.0f;//第一根绳的位置Y 5550 - 550   5600
const float Rope_Psition_Y2 =5780.0f;//第二根绳的位置Y 6310 - 550   6330(5780)
const float Column_Position_X =3225.0f;
const float Column_Position_Y1 =3000.0f;
const float Column_Position_Y2 =4500.0f; 
const float Column_Position_Y3 =6000.0f; 
const float First_line_restart_X =-680.0f;
const float First_line_restart_Y =3265.0f;
const float Second_line_restart_X =660.0f;
const float Second_line_restart_Y =4500.0f;//4400  4500

const float Test_position_Y_to_First_rope =890.0f;
const float Hill_Position_Y =6425.0f;
const float Camera_System_x = 0.0f;//-1230.0f; //1170+50   30摄像头与车坐标系的距离
const float Camera_System_y = 0.0f;//602.0f; //1200-50    30

const float Position_Test_X =1200.0f;
const float Position_Test_Y =4105.0f;

const float Distance_Beyond_Step =400.0f; //跨台阶时，跨过台阶那一步对于台阶前端的距离，台阶本身长300mm
const float Laser_Position_Y1_Red =660.0f;  //转向位置，激光对于台阶的距离
const float Laser_Position_Y1_Blue =1240.0f;

const float Hill_Position_X =-1280.0f;
const float Rplidar_position_X =0.0f;
const float Rplidar_position_Y =610.0f;//圆心
const float Rplidar_diameter =70.0f;

const float camera_position_x = 0.0f;
const float camera_position_y = -20.0f;


void FieldParaInit()
{
	if(field_direction>0)
	{
		RedFieldParaInit();
	}
	else
	{
		BlueFieldParaInit();
	}
	
	InstallationLocation *IL = &installation;
	SetFieldPara(&(*IL).camera_position,0.0f,0.0f);
	SetFieldPara(&(*IL).rplidar_position,0.0f,610.0f);
}

void RedFieldParaInit()
{
	FieldPara *red_field = &current_field;
	SetFieldPara(&(*red_field).initial_position,-680.0f,0.0f);
	SetFieldPara(&(*red_field).first_line_pre_position,-680.0f,2160.0f);
	SetFieldPara(&(*red_field).first_line_position,-680.0f,3160.0f);
	SetFieldPara(&(*red_field).first_redline_position,-680.0f,3400.0f);
	SetFieldPara(&(*red_field).first_line_restart,-680.0f,3265.0f);
	SetFieldPara(&(*red_field).second_line_restart,660.0f,4400.0f);
	SetFieldPara(&(*red_field).first_rope_position,0.0f,5550.0f);
	SetFieldPara(&(*red_field).second_rope_position,0.0f,6310.0f);
	SetFieldPara(&(*red_field).second_turn_position,950.0f,0.0f);
	SetFieldPara(&(*red_field).hill_position,-1280.0f,6425.0f);
	
	SetFieldPara(&(*red_field).first_redline_test,950.0f,3265.0f);
	SetFieldPara(&(*red_field).second_redline_test,950.0f,current_field.first_rope_position.y - 1000.0f);
	
	SetFieldPara(&(*red_field).first_column,3225.0f,2950.0f);
	SetFieldPara(&(*red_field).second_column,3225.0f,4450.0f);
	SetFieldPara(&(*red_field).third_column,3225.0f,5950.0f);
}

void BlueFieldParaInit()
{
	FieldPara *blue_field = &current_field;
	SetFieldPara(&(*blue_field).initial_position,-520.0f,0.0f);
	SetFieldPara(&(*blue_field).first_line_pre_position,-520.0f,2160.0f);
	SetFieldPara(&(*blue_field).first_line_position,-680.0f,3120.0f);
	SetFieldPara(&(*blue_field).first_redline_position,-680.0f,3400.0f);
	SetFieldPara(&(*blue_field).first_line_restart,-680.0f,3265.0f);
	SetFieldPara(&(*blue_field).second_line_restart,660.0f,4400.0f);
	SetFieldPara(&(*blue_field).first_rope_position,0.0f,5580.0f);
	SetFieldPara(&(*blue_field).second_rope_position,0.0f,6340.0f);
	SetFieldPara(&(*blue_field).second_turn_position,950.0f,0);
	SetFieldPara(&(*blue_field).hill_position,-1280.0f,6420.0f);
	
	SetFieldPara(&(*blue_field).first_redline_test,950.0f,3265.0f);
	SetFieldPara(&(*blue_field).second_redline_test,950.0f,current_field.first_rope_position.y - 1000.0f);
	
	SetFieldPara(&(*blue_field).first_column,3225.0f,2950.0f);
	SetFieldPara(&(*blue_field).second_column,3225.0f,4450.0f);
	SetFieldPara(&(*blue_field).third_column,3225.0f,5950.0f);
}

void SetFieldPara(PointPosition *pos,float set_x,float set_y)
{
	(*pos).x = set_x;
	(*pos).y = set_y;
}
