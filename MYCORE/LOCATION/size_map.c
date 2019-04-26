#include "size_map.h"

const float field_direction = -1.0f;

const float DM_radio = 0.57596f;//   66pi��3.141592654��/360  //motor_angle * radio = real distance
const float RM_radio = 0.265625f;//0.32075f;//34:128 //motor_angle * radio = real angle
const float RM_angle_min = 3.0f;
const float RM_angle_max = 70.0f;

const float Half_Length = 275.0f;
const float Half_Width = 310.0f;
const float Aluminum_Tube_Width = 25.0f;
const float laser_radio = 1.625;  //6.5:4

	 
	 /*��Զ�λ����ϵ*/
const float Redline_Position_Prepare =1480.0f;//��ʼ׼��ת���λ�ã���ʼ�������ࣩ
const float Initial_Position_Y= 25.0f;
const float Redline_Position_X1= -510.0f;///-630////-950//-510 //��һ��ת��λ��X
const float Redline_Position_Y1 =3160.0f;//1000//3160//3950 //��һ��ת��λ��Y
const float Oblique_PositionTurn_X= 950.0f;//�ڶ���ת��λ��X
const float Rope_Psition_Y1 =5000.0f;//��һ������λ��Y 5550 - 550
const float Rope_Psition_Y2 =5760.0f;//�ڶ�������λ��Y
const float Column_Position_X =3225.0f;
const float Column_Position_Y1 =3000.0f;
const float Column_Position_Y2 =4500.0f; 
const float Column_Position_Y3 =6000.0f; 
const float First_line_restart_X =-680.0f;
const float First_line_restart_Y =3265.0f;
const float Second_line_restart_X =660.0f;
const float Second_line_restart_Y =4400.0f;

const float Test_position_Y_to_First_rope =890.0f;
const float Hill_Position_Y =6425.0f;
const float Camera_System_x = -1230.0f; //1170+50   30����ͷ�복����ϵ�ľ���
const float Camera_System_y = 630.0f; //1200-50    30

const float Position_Test_X =1200.0f;
const float Position_Test_Y =4105.0f;

const float Distance_Beyond_Step =400.0f; //��̨��ʱ�����̨����һ������̨��ǰ�˵ľ��룬̨�ױ���300mm
const float Laser_Position_Y1_Red =660.0f;  //ת��λ�ã��������̨�׵ľ���
const float Laser_Position_Y1_Blue =1240.0f;

const float Hill_Position_X =-1280.0f;
const float Rplidar_position_X =0.0f;
const float Rplidar_position_Y =610.0f;//Բ��
const float Rplidar_diameter =70.0f;

const float camera_position_x = 0.0f;
const float camera_position_y = -20.0f;