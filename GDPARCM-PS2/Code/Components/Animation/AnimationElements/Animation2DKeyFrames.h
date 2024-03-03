#pragma once
#include <SFML/Graphics.hpp>

struct Animation2DKeyFrames
{
	sf::Sprite* sprite;
	float keyTime;

	bool operator==(const Animation2DKeyFrames& frameToCompare)
	{
		return (this->sprite == frameToCompare.sprite);
	}
};