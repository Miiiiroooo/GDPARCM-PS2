#pragma once
#include "AnimationParameter.h"
#include "Animation2D.h"

struct Transition
{
	AnimationParameter* parameter;
	Animation2D* animation;
	int intCondition;
	float floatCondition;
	bool boolCondition;

	Transition(AnimationParameter* parameter, Animation2D* animation) : parameter(parameter), animation(animation)
	{
		intCondition = 0;
		floatCondition = 0.0f;
		boolCondition = false;
	}
};