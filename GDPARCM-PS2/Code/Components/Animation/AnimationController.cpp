#include "AnimationController.h"
#include <algorithm>
#include <rapidjson/filereadstream.h>
#include "../../Managers/TextureManager.h"
#include "../../GameObjects/AGameObject.h"

AnimationController::AnimationController(std::string compName, Renderer* renderer, std::string jsonAnimationDataPath)
	: AComponent(compName, EComponentTypes::Animation), renderer(renderer), jsonAnimationDataPath(jsonAnimationDataPath)
{
	currentAnimationState = NULL;
	isFlipped = false;
}

AnimationController::~AnimationController()
{
	for (int i = animationsList.size() - 1; i >= 0; i--)
	{
		delete animationsList[i];
	}

	animationsList.clear();
	animationsList.shrink_to_fit();

	for (int i = parametersList.size() - 1; i >= 0; i--)
	{
		delete parametersList[i];
	}

	parametersList.clear();
	parametersList.shrink_to_fit();

	animationsGraph.clear();
}

#pragma region Initialization
void AnimationController::InitializeAnimations(std::vector<std::string> animationNamesList) 
{
	// open up the json file and parse its data into a variable
	FILE* inFile = fopen(jsonAnimationDataPath.c_str(), "rb");
	assert(inFile != NULL);

	char readBuffer[4096];
	rapidjson::FileReadStream jsonFile(inFile, readBuffer, sizeof(readBuffer));
	rapidjson::Document doc;

	doc.ParseStream(jsonFile);
	fclose(inFile);


	std::unordered_map<std::string, std::vector<std::pair<std::string, std::string>>> tempGraph; 

	// initialize all animations and animationParameters
	for (rapidjson::Value::ConstMemberIterator anm_itr = doc["animations"].MemberBegin(); anm_itr != doc["animations"].MemberEnd(); ++anm_itr) 
	{
		std::string animationName = anm_itr->name.GetString();

		if (std::find(animationNamesList.begin(), animationNamesList.end(), animationName) != animationNamesList.end())
		{
			// initialize default animation values
			float duration = anm_itr->value["duration"].GetFloat();
			bool isLooping = anm_itr->value["isLooping"].GetBool();
			float scaling = anm_itr->value["scaling"].GetFloat(); 

			// initialize animation key frames
			std::vector<Animation2DKeyFrames> keyFramesList;
			RetrieveAnimationKeyFrames(anm_itr, scaling, keyFramesList);

			// create new anim
			Animation2D* newAnim = new Animation2D(animationName, duration, isLooping, keyFramesList.front()); 
			newAnim->AddKeyFrames(keyFramesList); 
			animationsList.push_back(newAnim); 

			if (anm_itr->value["isDefault"].GetBool()) 
			{
				currentAnimationState = newAnim; 
			}

			// initialize transition to other anims
			std::vector<Transition> transitionsList;
			std::vector<std::pair<std::string, std::string>> paramToAnimMap;
			RetrieveTransitions(anm_itr, transitionsList, paramToAnimMap);

			animationsGraph[newAnim] = transitionsList;
			tempGraph[animationName] = paramToAnimMap;
		}
	}

	// remap all the new animations in each of the transition
	for (auto& animData : animationsGraph)
	{
		std::string animationName = animData.first->GetAnimationStateName();
		std::vector<std::pair<std::string, std::string>> paramToAnimMap = tempGraph[animationName];

		for (int i = 0; i < animData.second.size(); i++)
		{
			Transition& transition = animData.second[i];
			Animation2D* adjAnim = CheckForExistingAnimation(paramToAnimMap[i].second); 

			if (transition.parameter->parameterName == paramToAnimMap[i].first && adjAnim != NULL)
			{
				transition.animation = adjAnim;
			}
			else
			{
				// delete invalid transition
				animData.second.erase(animData.second.begin() + i);
			}
		}
	}

	// update renderer to the first frame
	sf::Sprite* firstFrame = currentAnimationState->GetCurrentSpriteAnimation(); 
	renderer->AssignDrawable(firstFrame); 
	if (owner != NULL) owner->UpdateSprite(firstFrame);  
}

void AnimationController::RetrieveAnimationKeyFrames(rapidjson::Value::ConstMemberIterator& anm_itr, float scaling, std::vector<Animation2DKeyFrames>& keyFramesList)
{
	for (rapidjson::Value::ConstMemberIterator key_itr = anm_itr->value["keyFrames"].MemberBegin(); key_itr != anm_itr->value["keyFrames"].MemberEnd(); ++key_itr) 
	{
		Animation2DKeyFrames newKeyFrame; 
		sf::Texture* texture = TextureManager::GetInstance()->GetTexture(key_itr->name.GetString()); 
		sf::Sprite* sprite = new sf::Sprite();

		sf::Vector2u origin = texture->getSize(); 
		origin.x /= 2;
		origin.y /= 2;
		sprite->setOrigin(origin.x, origin.y);  
		sprite->setTexture(*texture); 
		sprite->setScale(scaling, scaling); 

		newKeyFrame.sprite = sprite; 
		newKeyFrame.keyTime = key_itr->value.GetFloat(); 
		keyFramesList.push_back(newKeyFrame);  
	} 
}

void AnimationController::RetrieveTransitions(rapidjson::Value::ConstMemberIterator& anm_itr, std::vector<Transition>& transitionsList, std::vector<std::pair<std::string, std::string>>& paramToAnimMap)
{
	for (rapidjson::Value::ConstMemberIterator trs_itr = anm_itr->value["transitions"].MemberBegin(); trs_itr != anm_itr->value["transitions"].MemberEnd(); ++trs_itr) 
	{
		std::string adjAnimationName = trs_itr->name.GetString();  
		std::string parameterName = trs_itr->value["parameterName"].GetString(); 
		EAnimationParameterTypes type = GetParameterTypeFromString(trs_itr->value["type"].GetString()); 
		paramToAnimMap.push_back(std::make_pair(parameterName, adjAnimationName)); 

		AnimationParameter* selectedParam = CheckForExistingParameter(parameterName); 
		if (selectedParam == NULL) 
		{
			selectedParam = new AnimationParameter(parameterName, type); 
			parametersList.push_back(selectedParam); 
		}

		Transition newTransition = Transition(selectedParam, NULL); 
		switch (type)
		{
			case Int_Greater:
			case Int_Lesser:
			case Int_Equal:
			case Int_NotEqual:
				newTransition.condition.intValue = trs_itr->value["condition"].GetInt();
				transitionsList.push_back(newTransition);
				break;
			case Float_Greater:
			case Float_Lesser:
				newTransition.condition.floatValue = trs_itr->value["condition"].GetFloat();
				transitionsList.push_back(newTransition);
				break;
			case Bool:
				newTransition.condition.boolValue = trs_itr->value["condition"].GetBool();
				transitionsList.push_back(newTransition);
				break;
			case Trigger:
			case Trigger_Finished:
				newTransition.condition.isTriggered = true;
				transitionsList.push_back(newTransition);
				break;
			default:
				break;
		}
	}

}
#pragma endregion

#pragma region Update_Parameters
void AnimationController::SetInt(std::string parameterName, int newValue)
{
	AnimationParameter* selectedParam = CheckForExistingParameter(parameterName);
	if (selectedParam != NULL)
	{
		selectedParam->currentValues.intValue = newValue; 
	}
}

void AnimationController::SetFloat(std::string parameterName, float newValue)
{
	AnimationParameter* selectedParam = CheckForExistingParameter(parameterName); 
	if (selectedParam != NULL) 
	{
		selectedParam->currentValues.floatValue = newValue;
	}
}

void AnimationController::SetBool(std::string parameterName, bool newValue)
{
	AnimationParameter* selectedParam = CheckForExistingParameter(parameterName); 
	if (selectedParam != NULL) 
	{
		selectedParam->currentValues.boolValue = newValue;
	}
}

void AnimationController::SetTrigger(std::string parameterName)
{
	AnimationParameter* selectedParam = CheckForExistingParameter(parameterName); 
	if (selectedParam != NULL) 
	{
		selectedParam->currentValues.isTriggered = true;
	}
}
#pragma endregion

void AnimationController::FlipSprite(bool isFlipped)
{
	this->isFlipped = isFlipped;
}

void AnimationController::Perform()
{
	if (currentAnimationState == NULL)
	{
		return;
	}

	// update animation and check for its next sprite
	currentAnimationState->UpdateAnimation(deltaTime.asSeconds());
	sf::Sprite* currentSprite = currentAnimationState->GetCurrentSpriteAnimation(); 

	sf::Vector2f scaling = currentSprite->getScale();
	if ((isFlipped && scaling.x > 0) || (!isFlipped && scaling.x < 0))
	{
		scaling.x *= -1;
	}

	currentSprite->setScale(scaling);
	renderer->AssignDrawable(currentSprite);
	owner->UpdateSprite(currentSprite);

	// check for any transitions
	std::vector<Transition> transitionsList = animationsGraph[currentAnimationState];

	for (auto& transition : transitionsList)
	{
		if (transition.parameter->CheckForTransition(transition.condition, currentAnimationState->IsAtTheEndOfFrame()))
		{
			currentAnimationState->ResetAnimation();
			transition.parameter->ResetCurrentValues();
			currentAnimationState = transition.animation;
			break;
		}
	}
}

#pragma region Private methods
AnimationParameter* AnimationController::CheckForExistingParameter(std::string parameterName)
{
	auto parameterPos = std::find_if(parametersList.begin(), parametersList.end(), [&](AnimationParameter* p) { 
		return (p->parameterName == parameterName); 
		}); 

	return (parameterPos != parametersList.end()) ? *parameterPos : NULL; 
}

Animation2D* AnimationController::CheckForExistingAnimation(std::string animationName)
{
	auto animationPos = std::find_if(animationsList.begin(), animationsList.end(), [&](Animation2D* anim) {
		return (anim->GetAnimationStateName() == animationName); 
		}); 

	return (animationPos != animationsList.end()) ? *animationPos : NULL;
}

EAnimationParameterTypes AnimationController::GetParameterTypeFromString(std::string paramTypeName)
{
	if (paramTypeName == "Int_Greater") { return Int_Greater; }
	else if (paramTypeName == "Int_Lesser") { return Int_Lesser; }
	else if (paramTypeName == "Int_Equal") { return Int_Equal; }
	else if (paramTypeName == "Int_NotEqual") { return Int_NotEqual; }
	else if (paramTypeName == "Float_Greater") { return Float_Greater; }
	else if (paramTypeName == "Float_Lesser") { return Float_Lesser; }
	else if (paramTypeName == "Bool") { return Bool; }
	else if (paramTypeName == "Trigger") { return Trigger; }
	else if (paramTypeName == "Trigger_Finished") { return Trigger_Finished; }
	else { return Unknown; } 
}
#pragma endregion