#pragma once
#include "AGameObject.h"

class FPSCounter : public AGameObject
{
public:
	FPSCounter();
	~FPSCounter();

	void Initialize() override;


private:
	sf::Text* counterDisplay;
};

