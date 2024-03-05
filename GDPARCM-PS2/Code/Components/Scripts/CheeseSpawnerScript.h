#pragma once
#include "../AComponent.h"
#include "../../ObjectPooling/GameObjectPool.h"

class CheeseSpawnerScript : public AComponent
{
public:
	CheeseSpawnerScript(int maxCheese);
	~CheeseSpawnerScript();

	void Perform() override;


private:
	const float CHEESE_SPAWN_TIME = 9.f;
	const float INCREASED_SPAWN_DELAY = 1.4f; // the more cheese in the scene, the longer the spawn time
	float elapsedTime;

	int maxCheese;
	int numCheese;

	sf::FloatRect traversableArea;
	GameObjectPool* cheesePool;
};