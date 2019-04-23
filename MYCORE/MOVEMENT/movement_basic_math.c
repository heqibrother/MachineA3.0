/**
 * @brief: Provide parameter calculation in motion process
 */

#include "movement_basic_math.h"
const float speed_curve_area_radio = 0.5; //speed_curve_area_radio*accelerate_time*target_speed = real_distance_walked
const float angle_to_radian_radio = 0.017453;//3.14159/180
static const float DM_speed_table[101] ;
static const float DM_time_left_table[101] ;
		
float LookUpDMSpeedTable(float value_t) {
	if(value_t<0)return 0;
	if(value_t >1)return 1;
  if (value_t == 1.0f) {
    return DM_speed_table[100];
  } else {
    float tan_value_scale = value_t * 100;
    int index = floor(tan_value_scale);
    return (DM_speed_table[index] +
            (tan_value_scale - index) *
                (DM_speed_table[index + 1] - DM_speed_table[index]));
  }
	//return 0;
}

float LookUpDMTimeTable(float value_distance) {//已走距离比例
	if(value_distance<0)return 0;
	if(value_distance >1)return 1;
	if(value_distance<=0.191847)
	{
		for(int i=0;i<51;i++)
		{
			if(value_distance>=DM_time_left_table[i]&&value_distance<=DM_time_left_table[i+1])
			{
				return ((float)i+
            (value_distance - DM_time_left_table[i] ) /
                (DM_time_left_table[i+1] - DM_time_left_table[i]))/100.0;
			}
		}
	}
	else
	{
				for(int i=51;i<101;i++)
		{
			if(value_distance>=DM_time_left_table[i]&&value_distance<=DM_time_left_table[i+1])
			{
				return ((float)i+
            (value_distance - DM_time_left_table[i] ) /
                (DM_time_left_table[i+1] - DM_time_left_table[i]))/100.0;
			}
		}
	}

	return 0;

}

//正弦1+sin(t*t1 - Pi/2)   t :0~1 t1:Pi/2
static const float DM_speed_table[101] = {
			0.0000,0.00024674,0.000986676,0.00221908,0.00394273,
			0.00615592,0.00885648,0.0120417,0.0157086,0.0198533,
			0.0244719,0.0295598,0.0351119,0.0411229,0.0475867,
			0.0544969,0.0618469,0.0696292,0.0778363,0.0864599,
			0.0954917,0.104923,0.114744,0.124945,0.135516,
			0.146447,0.157727,0.169344,0.181288,0.193547,
			0.206108,0.218959,0.232087,0.245479,0.259123,
			0.273005,0.287111,0.301426,0.315938,0.330631,
			0.345492,0.360505,0.375655,0.390928,0.406309,
			0.421783,0.437333,0.452946,0.468605,0.484295,
			0.5,0.515705,0.531395,0.547054,0.562667,
			0.578217,0.593691,0.609072,0.624345,0.639495,
			0.654508,0.669369,0.684062,0.698574,0.712889,
			0.726995,0.740877,0.754521,0.767913,0.781042,
			0.793892,0.806453,0.818712,0.830656,0.842273,
			0.853553,0.864484,0.875055,0.885256,0.895077,
			0.904508,0.91354,0.922164,0.930371,0.938153,
			0.945503,0.952413,0.958877,0.964888,0.97044,
			0.975528,0.980147,0.984291,0.987958,0.991144,
			0.993844,0.996057,0.997781,0.999013,0.999753,1.0};

			//0.5*(t - sin(t*t1)/t1)   t1 :Pi  t:0~1
		static const float DM_time_left_table[101] = {
			0,0.000001,0.00001,0.00004,0.000105193,
			0.000205363,0.000354674,0.000562849,0.000839549,0.00119437,
			0.00163683,0.00217637,0.00282231,0.00358389,0.00447023,
			0.00549033,0.00665303,0.00796707,0.00944102,0.0110833,
			0.0129021,0.0149056,0.0171016,0.0194979,0.0221019,
			0.0249209,0.027962,0.0312322,0.034738,0.0384858,
			0.0424818,0.046732,0.051242,0.0560172,0.0610628,
			0.0663837,0.0719845,0.0778695,0.0840428,0.0905082,
			0.0972692,0.104329,0.11169,0.119356,0.127328,
			0.135609,0.1442,0.153103,0.162318,0.171847,
			0.18169,0.191847,0.202318,0.213102,0.2242,//11行
			0.235609,0.247328,0.259356,0.27169,0.284329,
			0.297269,0.310508,0.324042,0.337869,0.351984,
			0.366383,0.381062,0.396017,0.411242,0.426732,
			0.442481,0.458485,0.474737,0.491232,0.507961,
			0.52492,0.542101,0.559497,0.577101,0.594905,
			0.612901,0.631083,0.64944,0.667966,0.686652,
			0.70549,0.724469,0.743583,0.762822,0.782176,
			0.801636,0.821194,0.840839,0.860562,0.880354,
			0.900205,0.920104,0.940044,0.960012,0.980001,1.0};
		
void CalMovementPosition(MotorMoveState *motor)
{
	MotorPositionData *position = &(*motor).position_data;
  MotorDistanceData *distance = &(*motor).distance_data;
  MotorTimeData *time = &(*motor).time_data;
  MotorSpeedData *speed = &(*motor).speed_data;
	switch(DM_MoveInfo.speed_data.speed_mode)
	{
		case kOnlyAccelerateStability:
				 (*position).finish_accelerate_position = (*position).start_position 
																								+ (*speed).speed_direction * CalRealPosition((*distance).distance_all /3);
				 (*position).finish_keepspeed_position = (*position).start_position 
																							  + (*speed).speed_direction * CalRealPosition((*distance).distance_all *4/5);
				 (*position).finish_decelerate_position = (*position).start_position 
																								+ (*speed).speed_direction * CalRealPosition((*distance).distance_all);
				 
			break;
		
		case kOnlyDecelerateStability:
					(*position).finish_accelerate_position = (*position).start_position 
																								+ (*speed).speed_direction * CalRealPosition((*distance).distance_all /5);
				 (*position).finish_keepspeed_position = (*position).start_position 
																							  + (*speed).speed_direction * CalRealPosition((*distance).distance_all *2/3);
				 (*position).finish_decelerate_position = (*position).start_position 
																								+ (*speed).speed_direction * CalRealPosition((*distance).distance_all);
			break;
																	
		case kBothStability:
				 (*position).finish_accelerate_position = (*position).start_position 
																								+ (*speed).speed_direction * CalRealPosition((*distance).distance_all /3);
				 (*position).finish_keepspeed_position = (*position).start_position 
																							  + (*speed).speed_direction * CalRealPosition((*distance).distance_all *2/3);
				 (*position).finish_decelerate_position = (*position).start_position 
																								+ (*speed).speed_direction * CalRealPosition((*distance).distance_all);
			break;
																																
		case kBothUnStablity:
				 (*position).finish_accelerate_position = (*position).start_position 
																								+ (*speed).speed_direction * CalRealPosition((*distance).distance_all /5);
				 (*position).finish_keepspeed_position = (*position).start_position 
																							  + (*speed).speed_direction * CalRealPosition((*distance).distance_all *6/7);
				 (*position).finish_decelerate_position = (*position).start_position 
																								+ (*speed).speed_direction * CalRealPosition((*distance).distance_all);
			break;
		
		default:
			break;
	}
	(*time).accelerate_time = (int32_t)(fabs((*position).finish_accelerate_position - (*position).start_position) / ((*speed).target_position_speed*360.0f / 60.0f /1000.0f)/speed_curve_area_radio);
	(*time).keepspeed_time = (int32_t)(fabs((*position).finish_keepspeed_position - (*position).finish_accelerate_position) / ((*speed).target_position_speed*360.0f / 60.0f/1000.0f));
	(*time).decelerate_time = (int32_t)(fabs((*position).finish_decelerate_position -(*position).finish_keepspeed_position) / ((*speed).target_position_speed*360.0f / 60.0f/1000.0f)/speed_curve_area_radio);
	(*distance).distance_accelerate = CalRealDistance(fabs((*position).finish_accelerate_position - (*position).start_position));
	(*distance).distance_decelerate = CalRealDistance(fabs((*position).finish_decelerate_position - (*position).finish_keepspeed_position));
}

void CalMovementSpeed()
{
	float speed_limmit;
	speed_limmit = DM_MoveInfo.distance_data.distance_all / 600 * 400;//参考60cm可以速度到400不打脚
	if(speed_limmit<DM_MoveInfo.speed_data.target_position_speed)
	{
	  DM_MoveInfo.speed_data.target_position_speed = speed_limmit;
	}
}

void JudgeMovementSafiety()
{	
	//先确定角度需求
     switch(kLegState)
		{
			case kHighLegMove:
			{                                                  //旋转角度及其保护
				if(leg_angle.lowleg_yaw - RM_angle_min > leg_angle.target_yaw)
				{
					leg_angle.target_yaw = leg_angle.lowleg_yaw - RM_angle_min;
				}
				else if(leg_angle.lowleg_yaw + RM_angle_max  < leg_angle.target_yaw )
				{
					leg_angle.target_yaw = leg_angle.lowleg_yaw + RM_angle_max;
				}
			}
			{                                                  //根据旋转角度设置前进安全距离
				if(DM_MoveInfo.distance_data.target_distance  < CalDMMinSafeDistance()+10)
				{
					 DM_MoveInfo.distance_data.target_distance= CalDMMinSafeDistance()+10;
				}
				if(DM_MoveInfo.distance_data.target_distance  > CalDMMaxSafeDistance())
				{
					 DM_MoveInfo.distance_data.target_distance = CalDMMaxSafeDistance();
				}
			}
				break;
			
			case kLowLegMove:
			{                                                  //旋转角度及其保护
				if(leg_angle.highleg_yaw+ RM_angle_min <leg_angle.target_yaw )
				{
					leg_angle.target_yaw = leg_angle.highleg_yaw + RM_angle_min;
				}
				else if(leg_angle.highleg_yaw -RM_angle_max > leg_angle.target_yaw )
				{
					leg_angle.target_yaw = leg_angle.highleg_yaw - RM_angle_max;
				}
			}
			{                                                  //根据旋转角度设置前进安全距离
				if(DM_MoveInfo.distance_data.target_distance  < CalDMMinSafeDistance()+10)
				{
					 DM_MoveInfo.distance_data.target_distance= CalDMMinSafeDistance()+10;
				}
				if(DM_MoveInfo.distance_data.target_distance  > CalDMMaxSafeDistance())
				{
					 DM_MoveInfo.distance_data.target_distance = CalDMMaxSafeDistance();
				}
			}
				break;
			
			default:
				break;
		}
}

float CalRealSpeed(float speed)
{
	float result = 0;
	result = speed/60.0f/1000.0f*(360.0f*DM_radio);
	return result;
}

float CalRealDistance(float position_D_value)
{
	float result = 0;
	result = position_D_value*DM_radio;
	return result;
}

float CalRealPosition(float distance_D_value)
{
	float result = 0;
	result = distance_D_value/DM_radio;
	return result;
}

float CalDMMinSafeDistance()
{
	float result = 0;
	result = 20;
	return result;
}

float CalDMMaxSafeDistance()
{
		float result = 0;
	if(kLegState == kHighLegMove)
	{
		if(leg_angle.target_yaw - leg_angle.lowleg_yaw == 0)
		{
			result = (Half_Length-70) ;
		}
		else
		{
	    result = (Half_Length-70) - Half_Width / tan((90 - 0.5*fabs(leg_angle.target_yaw - leg_angle.lowleg_yaw))*angle_to_radian_radio);
		}
	}
	else if(kLegState == kLowLegMove)
	{
		if(leg_angle.target_yaw - leg_angle.highleg_yaw == 0)
		{
			result = (Half_Length-70)  ;
		}
		else
		{
		  result = (Half_Length-70)  - Half_Width / tan((90 - 0.5*fabs(leg_angle.target_yaw - leg_angle.highleg_yaw))*angle_to_radian_radio);
		}
	}
	return result;
}