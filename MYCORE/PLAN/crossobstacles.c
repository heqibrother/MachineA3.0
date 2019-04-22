#include "crossobstacles.h"

float CrossRope(float distance_hope,float rope_position,float ground_leg_position,float suspend_leg_position,Obstacle *targetobstacle)
{
	float result=0;
	float length_car = 545;//��ȥһ�����ܿ��
  if(rope_position>suspend_leg_position)//�ϰ�������ǰ
	{
		//����ǰ���Ƿ��п�������
		if(ConsideStepDistance(&result,rope_position-ground_leg_position,distance_hope,targetobstacle))
		{
			SetObstacleLocation(result,5,targetobstacle);
		}
		else
		{
			(*targetobstacle).obstacle_exist = false;
		}
		
		//��������Ƿ��п�������
		if((*targetobstacle).obstacle_exist)
		{
				rope_position = rope_position + length_car;
				if(ConsideStepDistance(&result,rope_position-ground_leg_position,distance_hope,targetobstacle))
				{
					SetObstacleLocation(result,5,targetobstacle);
				}
		}
	}
	else if(rope_position>suspend_leg_position-length_car)//�ϰ�������֮��
	{
		rope_position = rope_position + length_car;
		if(ConsideStepDistance(&result,rope_position-ground_leg_position,distance_hope,targetobstacle))
		{
			SetObstacleLocation(result,5,targetobstacle);
		}
		else
		{
			(*targetobstacle).obstacle_exist = false;
		}
	}
	return result;
}

bool ConsideStepDistance(float *result,float obstacle_distance,float distance_hope,Obstacle *obstacle)
{
	float warning_distance_after_obstacle = 107;//��Ϊ�������ܺ�Ϊԭ�㣬����ǰ����һ����
	float warning_distance_before_obstacle = 132.5;
	if(obstacle_distance + warning_distance_after_obstacle < distance_hope)//�ж��Ƿ����Կ���
	{
		*result = distance_hope;
		return true;
	}
	else
	{
		if(obstacle_distance - warning_distance_before_obstacle < distance_hope)//�ж��Ƿ��Ծ��Σ����
		{
		  *result = obstacle_distance - warning_distance_before_obstacle;
		}
		else 
			*result = distance_hope;//����Ծ��Σ����������ԭ״
		return false;
	}
	return false;
}

float DoubleJudgeCrossRope(float distance_hope,float rope_position1,float rope_position2,float ground_leg_position,float suspend_leg_position)
{
	float result = 0;
	result = CrossRope(distance_hope,rope_position1,ground_leg_position,suspend_leg_position,&obstacle1);
	result = CrossRope(result,rope_position2,ground_leg_position,suspend_leg_position,&obstacle2);
	result = CrossRope(result,rope_position1,ground_leg_position,suspend_leg_position,&obstacle1);//���µĲ������obstacle1��־
	return result;
}