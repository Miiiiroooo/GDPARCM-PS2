#pragma once
#include "AnimationParameter.h"
#include "Animation2D.h"
#include "AnimationParameterValues.h"

struct Transition
{
	AnimationParameter* parameter;
	Animation2D* animation;
	AnimationParameterValues condition;

	Transition(AnimationParameter* parameter, Animation2D* animation) : parameter(parameter), animation(animation)
	{
		condition.intValue = 0;
		condition.floatValue = 0;
		condition.boolValue = false;
		condition.isTriggered = false;
	}
};