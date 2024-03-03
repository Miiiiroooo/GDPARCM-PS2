#pragma once
#include <string>
#include "EAnimationParameterTypes.h"

class AnimationParameter
{
public:
	AnimationParameter(std::string parameterName, EAnimationParameterTypes type);
	~AnimationParameter();

	template<typename T> bool CheckForTransition(T value);


public:
	std::string parameterName; 
	int intValue;
	float floatValue;
	bool boolValue;
	bool isTriggered;

private:
	EAnimationParameterTypes type;
};


// must be in header >:(
template<typename T>
inline bool AnimationParameter::CheckForTransition(T value)
{
	bool willTransition = false;

	if ((type == Int_Greater && value > intValue) ||
		(type == Int_Lesser && value < intValue) ||
		(type == Int_Equal && value == intValue) ||
		(type == Int_NotEqual && value != intValue) ||
		(type == Float_Greater && value > floatValue) ||
		(type == Float_Lesser && value < floatValue) ||
		(type == Bool && value == boolValue) ||
		(type == Trigger && isTriggered))
	{
		willTransition = true;
	}

	return willTransition;
}
