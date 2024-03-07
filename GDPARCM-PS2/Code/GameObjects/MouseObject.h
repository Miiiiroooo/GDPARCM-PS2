#pragma once
#include "AGameObject.h"

class MouseObject : public AGameObject
{
public:
	MouseObject(sf::FloatRect area);
	~MouseObject();

	void Initialize() override;


private:
	sf::FloatRect playableArea;
};

