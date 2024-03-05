#pragma once
#include "../GameObjects/AGameObject.h"

class InteractiveLoadingScreen : public AGameObject
{
public:
	InteractiveLoadingScreen();
	~InteractiveLoadingScreen();

	void Initialize() override;
};