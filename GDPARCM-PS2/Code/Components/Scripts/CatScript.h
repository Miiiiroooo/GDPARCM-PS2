#pragma once
#include <SFML/Audio.hpp>
#include "../AComponent.h"
#include "../Animation/AnimationController.h"
#include "../../Physics/Collider.h"
#include "../../Enums/ECatStates.h"

class CatScript : public AComponent
{
public:
	CatScript(sf::FloatRect area, AnimationController* animController, Collider* collider);
	~CatScript();

	void SetMouse(AGameObject* mouse);
	void OnSceneTransition();
	//void OnSceneTransitionPounce();
	void Perform() override;

private:
	float GetRandomDelay();
	void OnDelay();
	void OnReady();
	void OnPounce();
	void HandleMovement();


private:
	AnimationController* animController;
	Collider* collider;
	AGameObject* mouse;
	sf::Sound* catMeowAudio;

	sf::FloatRect playableArea;
	bool isFlipped;

	const float POUNCE_TRAVEL_TIME = 1.05f;
	const float TIME_FRAME_TO_POUNCE = 0.7329f;
	const float MIN_DELAY = 0.65f;
	const float MAX_DELAY = 1.85f;

	float currentDelayTime;
	float elapsedTime;
	bool isOnSceneTransition;
	ECatStates currentState;
	sf::Vector2f travelSpeed;
};