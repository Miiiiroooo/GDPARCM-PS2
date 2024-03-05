#pragma once
#include "../AComponent.h"
#include "../Input/MouseController.h"
#include "../Animation/AnimationController.h"

class MouseScript : public AComponent
{
public:
	MouseScript(AGameObject* mouseObj, MouseController* inputController, AnimationController* animController);
	~MouseScript();

	void Perform() override;


private:
	AGameObject* mouseObj;
	MouseController* inputController;
	AnimationController* animController;

	const float MOVE_SPEED = 7.5f;
	bool isFlipped;
};

