#include "AnimationController.h"
#include <algorithm>
#include <rapidjson/document.h>
#include <rapidjson/filereadstream.h>
#include "../../Managers/TextureManager.h"


AnimationController::AnimationController(std::string compName, std::string jsonAnimationDataPath) : AComponent(compName, EComponentTypes::Animation), jsonAnimationDataPath(jsonAnimationDataPath)
{

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


	std::unordered_map<std::string, std::vector<std::tuple<std::string, std::string>>> tempGraph; 

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
			std::vector<Animation2DKeyFrames> keyFramesList;

			// initialize animation key frames
			for (rapidjson::Value::ConstMemberIterator key_itr = anm_itr->value["keyFrames"].MemberBegin(); key_itr != anm_itr->value["keyFrames"].MemberEnd(); ++key_itr) 
			{
				Animation2DKeyFrames newKeyFrame;
				sf::Texture* texture = TextureManager::GetInstance()->GetTexture(key_itr->name.GetString()); 
				sf::Sprite* sprite = new sf::Sprite(); 
				sprite->setTexture(*texture); 
				sprite->setScale(scaling, scaling);

				newKeyFrame.sprite = sprite;
				newKeyFrame.keyTime = key_itr->value.GetFloat();
				keyFramesList.push_back(newKeyFrame);
			}

			// create new anim
			Animation2D* newAnim = new Animation2D(animationName, duration, isLooping, keyFramesList.front());
			animationsList.push_back(newAnim);

			if (anm_itr->value["isDefault"].GetBool())
			{
				currentAnimationState = newAnim;
			}

			// initialise transition to other anims
			std::vector<Transition> transitionsList;
			for (rapidjson::Value::ConstMemberIterator trs_itr = anm_itr->value["transitions"].MemberBegin(); trs_itr != anm_itr->value["transitions"].MemberEnd(); ++trs_itr)
			{
				std::string adjAnimationName = trs_itr->name.GetString();
				std::string parameterName = trs_itr->value["parameter"].GetString();
				EAnimationParameterTypes type = GetParameterTypeFromString(trs_itr->value["type"].GetString()); 

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
						newTransition.intCondition = trs_itr->value["condition"].GetInt();
						transitionsList.push_back(newTransition);
						break;
					case Float_Greater: 
					case Float_Lesser: 
						newTransition.floatCondition = trs_itr->value["condition"].GetFloat();
						transitionsList.push_back(newTransition);
						break;
					case Bool:
						newTransition.boolCondition = trs_itr->value["condition"].GetBool();
						transitionsList.push_back(newTransition);
						break;
					case Trigger:
						transitionsList.push_back(newTransition);
						break;
					default:
						break;
				}
			}
			// todo: link succeeding anims to the old transitions;
		}
	}
}

void AnimationController::SetInt(std::string parameterName, int newValue)
{
	AnimationParameter* selectedParam = CheckForExistingParameter(parameterName);
	if (selectedParam != NULL)
	{
		selectedParam->intValue = newValue; 
	}
}

void AnimationController::SetFloat(std::string parameterName, float newValue)
{
	AnimationParameter* selectedParam = CheckForExistingParameter(parameterName); 
	if (selectedParam != NULL) 
	{
		selectedParam->floatValue = newValue;
	}
}

void AnimationController::SetBool(std::string parameterName, bool newValue)
{
	AnimationParameter* selectedParam = CheckForExistingParameter(parameterName); 
	if (selectedParam != NULL) 
	{
		selectedParam->boolValue = newValue;
	}
}

void AnimationController::SetTrigger(std::string parameterName)
{
	AnimationParameter* selectedParam = CheckForExistingParameter(parameterName); 
	if (selectedParam != NULL) 
	{
		selectedParam->isTriggered = true;
	}
}

void AnimationController::Perform()
{

}

AnimationParameter* AnimationController::CheckForExistingParameter(std::string parameterName)
{
	auto parameterPos = std::find_if(parametersList.begin(), parametersList.end(), [&](const AnimationParameter& p) { 
		return (p.parameterName == parameterName); 
		}); 

	return (parameterPos != parametersList.end()) ? *parameterPos : NULL; 
}

//Animation2D* AnimationController::CheckForExistingAnimation(std::string animationName)
//{
//	auto animationPos = std::find_if(animationsList.begin(), animationsList.end(), [&](Animation2D& anim) {
//		return (anim.GetAnimationStateName() == animationName);
//		}); 
//
//	return (animationPos != animationsList.end()) ? *animationPos : NULL;
//}

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
	else { return Unknown; } 
}