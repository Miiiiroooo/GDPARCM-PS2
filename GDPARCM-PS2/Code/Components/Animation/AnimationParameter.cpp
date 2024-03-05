#include "AnimationParameter.h"

AnimationParameter::AnimationParameter(std::string parameterName, EAnimationParameterTypes type) : parameterName(parameterName), type(type)
{
	currentValues.intValue = 0;
	currentValues.floatValue = 0.f;
	currentValues.boolValue = false;
	currentValues.isTriggered = false;
}

AnimationParameter::~AnimationParameter()
{

}

bool AnimationParameter::CheckForTransition(AnimationParameterValues condition)
{
	bool willTransition = false;

	if ((type == Int_Greater && currentValues.intValue > condition.intValue) ||
		(type == Int_Lesser && currentValues.intValue < condition.intValue) ||
		(type == Int_Equal && currentValues.intValue == condition.intValue) ||
		(type == Int_NotEqual && currentValues.intValue != condition.intValue) ||
		(type == Float_Greater && currentValues.floatValue > condition.floatValue) ||
		(type == Float_Lesser && currentValues.floatValue < condition.floatValue) ||
		(type == Bool && currentValues.boolValue == condition.boolValue) ||
		(type == Trigger && currentValues.isTriggered))
	{
		willTransition = true;
	}

	return willTransition;
}
