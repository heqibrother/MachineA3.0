#include "securitydetection.h"

SecurityItems securityitem;
SecurityLedState RedState,GreenState,BlueState;

void SecurityStateInit()
{
	securityitem.sGeneralState.State = kSecurityUnknow;
	securityitem.sMotorState.State = kSecurityUnknow;
	securityitem.sLegState.State = kSecurityUnknow;
}

void JudgeSecurityState()
{
	SetTwinkParameter(JudgeMotorStateSecurity(),&RedState);
	SetTwinkParameter(JudgeRotateMotorSecurity(),&GreenState);
	SetTwinkParameter(JudgeGyroscopeSecurity(),&BlueState);
}

SecurityState JudgeGeneralStateSecurity()
{
	if(kMachineAGeneralState == kClamberModeWaiting)
	{
		securityitem.sGeneralState.last_time_confirm_security = MyGetTime();
		securityitem.sGeneralState.State = kSecurityConfirm;
	}
	else
		securityitem.sGeneralState.State = kSecurityDestroyed;
	switch(securityitem.sGeneralState.State)
	{
		case kSecurityConfirm:
			break;
		
		case kSecurityDestroyed:	
			if(MyGetTime() - securityitem.sGeneralState.last_time_confirm_security > 50)
			  securityitem.sGeneralState.State = kSecurityUnknow;
			else break;

		case kSecurityUnknow:
			break;
		
		case kStopJudgeSecurity:
			break;
		
	  default:
			break;
	}
	return securityitem.sGeneralState.State;
}

SecurityState JudgeMotorStateSecurity()
{
	if(securityitem.sMotorState.refresh_flag)
	{
		securityitem.sMotorState.last_time_confirm_security = MyGetTime();
		securityitem.sMotorState.State = kSecurityConfirm;
		securityitem.sMotorState.refresh_flag = false;
	}
	else
		securityitem.sMotorState.State = kSecurityDestroyed;
	switch(securityitem.sMotorState.State)
	{
		case kSecurityConfirm:
			break;
		
		case kSecurityDestroyed:	
//			if(MyGetTime() - securityitem.sMotorState.last_time_confirm_security > 50)
//			  securityitem.sMotorState.State = kSecurityUnknow;
			//else 
				break;

		case kSecurityUnknow:
			break;
		
		case kStopJudgeSecurity:
			break;
		
	  default:
			break;
	}
	return securityitem.sMotorState.State;
}

SecurityState JudgeLegState()
{
	if(!leg_data_feedback.send_leg_change_flag)//&&!leg_data_feedback.send_leg_height_change_flag)
	{
		securityitem.sLegState.last_time_confirm_security = MyGetTime();
		securityitem.sLegState.State = kSecurityConfirm;
	}
	else
		securityitem.sLegState.State = kSecurityDestroyed;
	switch(securityitem.sLegState.State)
	{
		case kSecurityConfirm:
			break;
		
		case kSecurityDestroyed:	
			if(MyGetTime() - securityitem.sLegState.last_time_confirm_security > 50)
			  securityitem.sLegState.State = kSecurityUnknow;
			else break;

		case kSecurityUnknow:
			break;
		
		case kStopJudgeSecurity:
			break;
		
	  default:
			break;
	}
	return securityitem.sLegState.State;
}

SecurityState JudgeGyroscopeSecurity()
{
	if(MyGetTime() - securityitem.sGyroscope.last_time_confirm_security < 50)//&&!leg_data_feedback.send_leg_height_change_flag)
	{
		securityitem.sGyroscope.State = kSecurityConfirm;
	}
	else
		securityitem.sGyroscope.State = kSecurityDestroyed;
	
	return securityitem.sGyroscope.State;
}

SecurityState JudgeRotateMotorSecurity()
{
	if(MyGetTime() - securityitem.RotateMotor.last_time_confirm_security < 50)//&&!leg_data_feedback.send_leg_height_change_flag)
	{
		securityitem.RotateMotor.State = kSecurityConfirm;
	}
	else
		securityitem.RotateMotor.State = kSecurityDestroyed;

	return securityitem.RotateMotor.State;
}

void SetTwinkParameter(SecurityState state,SecurityLedState *ledstate)
{
		switch(state)
	{
		case kSecurityConfirm:
			(*ledstate).dark_time = 200;
		  (*ledstate).light_time = 200;
			break;
		
		case kSecurityDestroyed:	
			(*ledstate).dark_time = 500;
		  (*ledstate).light_time = 0;
		 break;

		case kSecurityUnknow:
			(*ledstate).dark_time = 500;
		  (*ledstate).light_time = 500;
			break;
		
		case kStopJudgeSecurity:
			(*ledstate).dark_time = 0;
		  (*ledstate).light_time = 500;
			break;
		
	  default:
			break;
	}
}

void LedIndicate(LED_TypeDef led,SecurityLedState *ledstate,int32_t current_time)
{
	(*ledstate).change_time = current_time%((*ledstate).light_time + (*ledstate).dark_time);
	if((*ledstate).change_time<((*ledstate).light_time))
	{
		LED_On(led);
	}
	else
	{
		LED_Off(led);
	}
//	if((*ledstate).state)
//	{
//		LED_On(led);
//		if(current_time - (*ledstate).change_light_time>(*ledstate).light_time&&(*ledstate).dark_time>50)
//		{
//			(*ledstate).state = false;
//			(*ledstate).change_dark_time = current_time;
//		}
//	}
//	else
//	{
//		LED_Off(led);
//		if(current_time - (*ledstate).change_dark_time>(*ledstate).dark_time&&(*ledstate).light_time>50)
//		{
//			(*ledstate).state = true;
//			(*ledstate).change_light_time = current_time;
//		}
//	}
}
