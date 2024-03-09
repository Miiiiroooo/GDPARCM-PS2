#pragma once
#include "../AGameObject.h"
#include "../../Components/Scripts/MouseScript.h"

class MouseObject : public AGameObject
{
public:
	MouseObject(sf::FloatRect area);
	~MouseObject();

	void Initialize() override;
	MouseScript* GetScript();


private:
	sf::FloatRect playableArea;
	MouseScript* script;
};

