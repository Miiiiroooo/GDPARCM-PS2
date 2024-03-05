#pragma once
#include <string>
#include "EAnimationParameterTypes.h"
#include "AnimationParameterValues.h"

class AnimationParameter
{
public:
	AnimationParameter(std::string parameterName, EAnimationParameterTypes type);
	~AnimationParameter();

	bool CheckForTransition(AnimationParameterValues condition);


public:
	std::string parameterName; 
	AnimationParameterValues currentValues;

private:
	EAnimationParameterTypes type;
};