#pragma once
#include "../AComponent.h"

class FPSCounterScript : public AComponent
{
public:
	FPSCounterScript();
	~FPSCounterScript();

	void Perform() override;
	void SetCounterDisplay(sf::Text* text);


private:
	const sf::Time UPDATE_TICKS = sf::seconds(0.5f);
	sf::Time updateTime; // seconds since last update
	sf::Text* counterDisplay;
};

