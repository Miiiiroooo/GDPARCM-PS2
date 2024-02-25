#include "FPSCounterScript.h"
#include "../../Game.h"

FPSCounterScript::FPSCounterScript() : AComponent("FPSCounterScript", EComponentTypes::Script)
{
	updateTime = sf::seconds(0.0f);
	counterDisplay = NULL;
}

FPSCounterScript::~FPSCounterScript()
{
	AComponent::~AComponent();
}

void FPSCounterScript::Perform()
{
	updateTime += deltaTime; 

	if (updateTime >= UPDATE_TICKS)  
	{
		updateTime = sf::seconds(0.0f); 
		this->counterDisplay->setString("FPS: " + std::to_string(Game::GetInstance()->GetFPS()) + "\n"); 
	}
}

void FPSCounterScript::SetCounterDisplay(sf::Text* text)
{
	this->counterDisplay = text;
}