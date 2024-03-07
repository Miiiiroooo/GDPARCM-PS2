#pragma once
#include "../AComponent.h"
#include "../../ObjectPooling/GameObjectPool.h"

class CheeseSpawnerScript : public AComponent
{
public:
	CheeseSpawnerScript(int maxCheese, sf::FloatRect area);
	~CheeseSpawnerScript();

	void Perform() override;
	
	void OnEatCheese(APoolable* cheese);


private:
	const float CHEESE_SPAWN_TIME = 2.5f;
	const float INCREASED_SPAWN_DELAY = 1.15f; // the more cheese in the scene, the longer the spawn time
	float elapsedTime;

	int maxCheese;
	int numCheese;

	sf::FloatRect playableArea;
	GameObjectPool* cheesePool;
};