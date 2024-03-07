#pragma once
#include "AGameObject.h"

class PlayableArea : public AGameObject
{
public:
	PlayableArea(sf::FloatRect rect);
	~PlayableArea();

	void Initialize() override;


private:
	sf::FloatRect rect;
};