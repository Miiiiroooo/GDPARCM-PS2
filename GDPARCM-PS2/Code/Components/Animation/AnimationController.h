#pragma once
#include <unordered_map>
#include "../AComponent.h"
#include "AnimationElements/Animation2D.h"
#include "AnimationElements/AnimationParameter.h"
#include "AnimationElements/Transition.h"


class AnimationController : public AComponent
{
public:
	AnimationController(std::string compName, std::string jsonAnimationDataPath = "Media/AnimationData.json");
	~AnimationController();

	void InitializeAnimations(std::vector<std::string> animationNamesList);
	void SetInt(std::string parameterName, int newValue);
	void SetFloat(std::string parameterName, float newValue);
	void SetBool(std::string parameterName, bool newValue);
	void SetTrigger(std::string parameterName);

	void Perform() override; 

private:
	AnimationParameter* CheckForExistingParameter(std::string parameterName);
	//Animation2D* CheckForExistingAnimation(std::string animationName);
	EAnimationParameterTypes GetParameterTypeFromString(std::string paramTypeName);


private:
	std::vector<Animation2D*> animationsList;
	std::vector<AnimationParameter*> parametersList;
	std::unordered_map<Animation2D*, std::vector<Transition>> animationsGraph;
	Animation2D* currentAnimationState;

	std::string jsonAnimationDataPath;
};