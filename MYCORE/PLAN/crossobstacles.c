#include "crossobstacles.h"

float CrossRope(float distance_hope,float rope_position,float ground_leg_position,float suspend_leg_position,Obstacle *targetobstacle)
{  float result = 0;
	//float result_first_leg=0;
	//float result_second_leg = 0;
	float length_car = 2*Half_Length;//��ȥһ�����ܿ��
  if(rope_position>suspend_leg_position)//�ϰ�������ǰ
	{
		//����ǰ���Ƿ��п�������
		if(ConsideStepDistance(&result,rope_position-ground_leg_position,distance_hope,targetobstacle))
		{
			SetObstacleLocation(rope_position - suspend_leg_position,5,targetobstacle);
		}
		else
		{
			(*targetobstacle).obstacle_exist = false;
		}
		
		//��������Ƿ��п�������
		if((*targetobstacle).obstacle_exist)
		{
				rope_position = rope_position + length_car;
				if(ConsideStepDistance(&result,rope_position-ground_leg_position,result,targetobstacle))
				{
					SetObstacleLocation(rope_position - suspend_leg_position,5,targetobstacle);
				}
				else
				{
						rope_position = rope_position - length_car;
					if(ConsideStepDistance(&result,rope_position-ground_leg_position,result,targetobstacle))
					{
						SetObstacleLocation(rope_position - suspend_leg_position,5,targetobstacle);
					}
					else
					{
						(*targetobstacle).obstacle_exist = false;
					}
				}
		}
//		else//ǰ�Ȳ�����
//		{
//			  rope_position = rope_position + length_car;
//				if(ConsideStepDistance(&result,rope_position-ground_leg_position,result,targetobstacle))
//				{
//					SetObstacleLocation(rope_position - suspend_leg_position,5,targetobstacle);
//				}
//				else
//				{
//					(*targetobstacle).obstacle_exist = false;
//				}
//		}
	}
	else if(rope_position>suspend_leg_position-length_car)//�ϰ�������֮��
	{
		rope_position = rope_position + length_car;
		if(ConsideStepDistance(&result,rope_position-ground_leg_position,distance_hope,targetobstacle))
		{
			SetObstacleLocation(rope_position - suspend_leg_position,5,targetobstacle);
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
	float warning_distance_before_obstacle = 107;//132.5;
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
			if(*result>CalDMMinSafeDistance())//���С����С����
			{
				return false;
			}
			else
			{
				*result = warning_distance_after_obstacle + obstacle_distance;
				return true;
			}
			return false;
		}
		else 
		{
			*result = distance_hope;//����Ծ��Σ����������ԭ״
		  return false;
		}
	}

	return false;
}

float DoubleJudgeCrossRope(float distance_hope,float rope_position1,float rope_position2,float ground_leg_position,float suspend_leg_position)
{
	float result = 0;
	result = CrossRope(distance_hope,rope_position1,ground_leg_position,suspend_leg_position,&obstacle1);
	result = CrossRope(result,rope_position2,ground_leg_position,suspend_leg_position,&obstacle2);
	result = CrossRope(result,rope_position1,ground_leg_position,suspend_leg_position,&obstacle1);//ȷ�Ͽ����ߵ���󲽾࣬����obstacle1��־
	result = CrossRope(result,rope_position2,ground_leg_position,suspend_leg_position,&obstacle2);//���µĲ������obstacle2��־
	return result;
}