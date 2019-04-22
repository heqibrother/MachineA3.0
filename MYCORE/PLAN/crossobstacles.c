#include "crossobstacles.h"

float CrossRope(float distance_hope,float rope_position,float ground_leg_position,float suspend_leg_position,Obstacle *targetobstacle)
{
	float result=0;
	float length_car = 545;//除去一个铝管宽度
  if(rope_position>suspend_leg_position)//障碍在两腿前
	{
		//计算前腿是否有跨绳问题
		if(ConsideStepDistance(&result,rope_position-ground_leg_position,distance_hope,targetobstacle))
		{
			SetObstacleLocation(result,5,targetobstacle);
		}
		else
		{
			(*targetobstacle).obstacle_exist = false;
		}
		
		//计算后腿是否有跨绳问题
		if((*targetobstacle).obstacle_exist)
		{
				rope_position = rope_position + length_car;
				if(ConsideStepDistance(&result,rope_position-ground_leg_position,distance_hope,targetobstacle))
				{
					SetObstacleLocation(result,5,targetobstacle);
				}
		}
	}
	else if(rope_position>suspend_leg_position-length_car)//障碍在两腿之间
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
	float warning_distance_after_obstacle = 107;//因为是以铝管后处为原点，所以前后有一点差距
	float warning_distance_before_obstacle = 132.5;
	if(obstacle_distance + warning_distance_after_obstacle < distance_hope)//判断是否足以跨绳
	{
		*result = distance_hope;
		return true;
	}
	else
	{
		if(obstacle_distance - warning_distance_before_obstacle < distance_hope)//判断是否会跃进危险区
		{
		  *result = obstacle_distance - warning_distance_before_obstacle;
		}
		else 
			*result = distance_hope;//不会跃进危险区，保持原状
		return false;
	}
	return false;
}

float DoubleJudgeCrossRope(float distance_hope,float rope_position1,float rope_position2,float ground_leg_position,float suspend_leg_position)
{
	float result = 0;
	result = CrossRope(distance_hope,rope_position1,ground_leg_position,suspend_leg_position,&obstacle1);
	result = CrossRope(result,rope_position2,ground_leg_position,suspend_leg_position,&obstacle2);
	result = CrossRope(result,rope_position1,ground_leg_position,suspend_leg_position,&obstacle1);//用新的步距更新obstacle1标志
	return result;
}