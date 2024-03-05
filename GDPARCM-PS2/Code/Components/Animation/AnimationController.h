#pragma once
#include <unordered_map>
#include <rapidjson/document.h>
#include "../AComponent.h"
#include "../Renderer.h"
#include "Animation2D.h"
#include "AnimationParameter.h"
#include "Transition.h"


class AnimationController : public AComponent
{
public:
	AnimationController(std::string compName, Renderer* renderer, std::string jsonAnimationDataPath = "Media/AnimationData.json");
	~AnimationController();

	void InitializeAnimations(std::vector<std::string> animationNamesList);

	void SetInt(std::string parameterName, int newValue);
	void SetFloat(std::string parameterName, float newValue);
	void SetBool(std::string parameterName, bool newValue);
	void SetTrigger(std::string parameterName);

	void FlipSprite(bool isFlipped);
	void Perform() override; 

private:
	void RetrieveAnimationKeyFrames(rapidjson::Value::ConstMemberIterator& anm_itr, float scaling, std::vector<Animation2DKeyFrames>& keyFramesList);
	void RetrieveTransitions(rapidjson::Value::ConstMemberIterator& anm_itr, std::vector<Transition>& transitionsList, std::vector<std::pair<std::string, std::string>>& paramToAnimMap);

	AnimationParameter* CheckForExistingParameter(std::string parameterName);
	Animation2D* CheckForExistingAnimation(std::string animationName); 
	EAnimationParameterTypes GetParameterTypeFromString(std::string paramTypeName);


private:
	std::string jsonAnimationDataPath;
	Renderer* renderer;
	bool isFlipped;

	std::vector<Animation2D*> animationsList;
	std::vector<AnimationParameter*> parametersList;
	std::unordered_map<Animation2D*, std::vector<Transition>> animationsGraph;
	Animation2D* currentAnimationState;
};