#include "AnimationParameter.h"

AnimationParameter::AnimationParameter(std::string parameterName, EAnimationParameterTypes type) : parameterName(parameterName), type(type)
{
	intValue = 0;
	floatValue = 0.f;
	boolValue = false;
	isTriggered = false;
}

AnimationParameter::~AnimationParameter()
{

}