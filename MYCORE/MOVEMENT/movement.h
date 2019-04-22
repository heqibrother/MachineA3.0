#ifndef __MOVEMENT_H
#define __MOVEMENT_H

#include "math.h"
#include "stm32f4xx.h"
#include "arm_math.h"
#include <stdbool.h>


/***�˶�ģʽ������***/
typedef enum 
{
	kSpeedFirst,//�ٶ�����ģʽ��ֱ�е����λ���ȣ�����ֱ�ж�
	kLocationFirst//��λ����ģʽ��ȷ���ȶ��ԣ����ڲ�׼������������̨�׵�
}MovementStyle;

/***�˶�ģʽ������***/
typedef enum 
{
  kOnlyAccelerateStability,//ֻ�ӳ����ٶ�
	kOnlyDecelerateStability,//ֻ�ӳ����ٶ�
	kBothStability,          //���ٶμ��ٶζ��ӳ�
	kBothUnStablity          //�����������ӳ�
}SpeedMode;//�����Ӽ���ʱ��

/***����˶�λ�����ݣ��Ƕ�Ϊ��λ��***/
typedef struct 
{
  float initial_position;//��¼�����ʱ�ĵ���Ƕ�ֵ����׼ʱ�̣������غϣ�
	
	float start_position;//ÿ����ʼ��λ��
	float finish_accelerate_position;//����ĵ��ֵ�ڵ�
	float finish_keepspeed_position;
	float finish_decelerate_position;
	
	float current_position;
	float record_position;
	float position_walked;
	float position_left;
}MotorPositionData;

/***����˶����Ծ������ݣ�����Ϊ��λ��***/
typedef struct 
{
	float target_distance;
	float distance_accelerate;
	float distance_decelerate;
	float distance_walked;//���߾���
	float distance_left;
	float distance_all;

}MotorDistanceData;

/***����˶�ʱ�����ݣ��׶���ʱ�䣩***/
typedef struct 
{
	int32_t start_time;//ÿ����ʼ��ʱ��
	int32_t accelerate_time;
	int32_t keepspeed_time;
	int32_t decelerate_time;
}MotorTimeData;

/***����˶��ٶ�����***/
typedef struct 
{
	float target_position_speed;//�Ե���Ƕ�Ϊ��λ
	float target_distance_speed;
	float current_expected_speed;
	float speed_direction;//�߰����л����ٶȷ���ȡ��ϵ��
	SpeedMode speed_mode;
}MotorSpeedData;

/***�ϰ���λ����Ϣ***/
typedef struct 
{
  bool obstacle_exist;//�ж���һ���Ƿ�����ϰ�
  //�ϰ�λ����ʵ��λ�ã��͵��������������ϵ
	float obstacle_location;
	float obstacle_width;
}Obstacle;

/***�˶���Ϣ�Ľṹ***/
typedef  struct 
{
	MotorPositionData position_data;
  MotorDistanceData distance_data;
  MotorTimeData time_data;
  MotorSpeedData speed_data;
	bool motor_position;//��־λ���жϵ���Ƿ�λ
}MotorMoveState;

/***���ƽṹ������ʱ��***/
typedef enum{                //ȫ��ʱ���־λ
	  kBeforeFurtherPlan,     //�������ϸ�Ĳ���
	  kBeforeRecoverLeg,      //δ����������
    kBeforeRiseItself,      //δ����������ָ���߶�
	  kBeforeLayDownLegs,     //δ������λ��
  	kBeforeSelfCorrection,  //δ�����Ծ���
	  kBeforeDMPosition,      //ֱ�е��δ��λ
	  kBeforeRMPosition,      //��ת���δ��λ
	  kBeforeLegTouchGround,  //���ȴ���
	  kAllDone                //���в����������
}TimePoint;

/***�˶������ŵص�ģʽ***/
typedef enum {//��״̬
    kHighLegMove,//�����ƶ��������ڵ�
	  kLowLegMove,
	  kAnyLegMove
}LegState;

/***�˶����ȵ�����***/
typedef struct 
{
	int leg_state_command;//�����ȵ�ָ������Ƿ�����
  int leg_state_number;//��ʱ�������ȵ�״̬����
	int leg_state_number_pre;//��¼״̬���ݣ��������л�ʱ����л�
	int leg_target_state_time;//��¼����һ��״̬��ʱ��
	int leg_safe_to_laydown;//1��ȫ 0����ȫ
}LegStateData;

/***�˶����ȷ��ص�����***/
typedef struct 
{
	int16_t leg_state_[4] ;//��¼ÿ���ȵ�״̬��˳����ǰ��ʱ�뵽�Һ�
	int leg_state_feedback;//���ص���״̬
	int crossd_step_state;
	bool crossed_step ;//�ж��Ƿ�Խ��̨��
}LegDataFeedback;

//�������ã�ȷ��Ӧ���е��ýṹ��ʱ���ṹ���Ѿ�������
#include "superstratum.h"
#include "DM_motor_movement.h"
#include "RM_motor_movement.h"
#include "leg_movement.h"
#include "movement_basic_math.h"
#include "angle_movement.h"

extern MotorMoveState DM_MoveInfo,RM_MoveInfo;
extern MovementStyle movement_style;
extern TimePoint time_point_for_speed,time_point_for_location;
extern Obstacle obstacle1,obstacle2;
/*********Function declaration*******/

/**
 * @brief: Execute motion planning according to different time points
 * @return: false(continue) / true(finish)
 * @status: 2019.4.14
 */
bool ExecutePlan();

/**
 * @brief: Executing the motion of the speed-first time point
 * @return: none
 * @status: 2019.4.14
 */
void SpeedFirstMode();

/**
 * @brief: Executing the motion of the location-first time point
 * @return: none
 * @status: 2019.4.14
 */
void LocationFirstMode();

/**
 * @brief: Calculate more detailed motion thresholds based on the target
 * @status: 2019.4.14
 */
void CalculateFurtherMovementData();

/**
 * @brief: Refresh the previous record before each step starts
 * @status: 2019.4.21
 */
void RefreshMovementDataEveryBegining();

/**
 * @brief: Determine whether you need to wait for your legs to be lifted in place
 * @return: true(need to wait) false(no)
 * @status: 2019.4.21
 */
bool SafeToMoveBeforeRecover();

/**
 * @brief: Determine if you need to wait for your legs to cross the barrier before putting them down
 * @return: true(need to wait) false(no)
 * @status: 2019.4.21
 */
bool SafeToLayDownBeforePosition();

/**
 * @brief: Detect errors in the initial decision based on location
 * @return: none
 * @status: 2019.4.21
 */
void SelfCorrection();

/**
 * @brief: set obstacles in one step
 * @param: position of obstacles , width of obstacles
 * @return: none
 * @status: 2019.4.21
 */
void SetObstacleLocation(float obstacleposition,float obstaclewidth,Obstacle *targetobstacle);

/**
 * @brief: Update regular motion data
 * @return: none
 * @status: 2019.4.21
 */
void RefreshMovementData();
#endif
