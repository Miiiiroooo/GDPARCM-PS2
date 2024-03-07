#pragma once
#include <SFML/Audio.hpp>
#include "../AComponent.h"
#include "../Input/MouseController.h"
#include "../Animation/AnimationController.h"
#include "../../Physics/Collider.h"
#include "HitBehaviorScript.h"

class MouseScript : public AComponent, public ICollisionListener
{
public:
	MouseScript(sf::FloatRect area, MouseController* inputController, AnimationController* animController, Collider* collider, HitBehaviorScript* hitScript);
	~MouseScript();

	void Perform() override;
	void OnCollisionEnter(AGameObject* collidedObj) override;
	void OnCollisionExit(AGameObject* collidedObj) override;

private:
	void HandleMovement(MouseController::KeyDictionary& keyInputs);
	sf::Vector2f ApplyMovementRestrictions(sf::Vector2f movement);


private:
	MouseController* inputController;
	AnimationController* animController;
	Collider* collider;
	HitBehaviorScript* hitScript;
	sf::Sound* mouseEatAudio;

	sf::FloatRect playableArea;
	const float MOVE_SPEED = 7.5f;
	bool isFlipped;
};

