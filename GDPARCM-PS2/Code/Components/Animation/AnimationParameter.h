#pragma once
#include <string>
#include "../../Enums/EAnimationParameterTypes.h"
#include "AnimationParameterValues.h"

class AnimationParameter
{
public:
	AnimationParameter(std::string parameterName, EAnimationParameterTypes type);
	~AnimationParameter();

	void ResetCurrentValues();
	bool CheckForTransition(AnimationParameterValues condition, bool isAtTheEndOfFrame);


public:
	std::string parameterName; 
	AnimationParameterValues currentValues;

private:
	EAnimationParameterTypes type;
};