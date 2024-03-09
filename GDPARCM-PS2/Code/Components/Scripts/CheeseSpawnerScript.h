#pragma once
#include "../AComponent.h"
#include "../../ObjectPooling/GameObjectPool.h"

class CheeseSpawnerScript : public AComponent
{
public:
	CheeseSpawnerScript(int maxCheese, sf::FloatRect area);
	~CheeseSpawnerScript();

	void InitializeSpawner();
	void Perform() override;
	
	void OnEatCheese(APoolable* cheese);
	void ReleaseAllCheese();


private:
	const float CHEESE_SPAWN_TIME = 2.0f;
	const float INCREASED_SPAWN_DELAY = 1.12f; // the more cheese in the scene, the longer the spawn time
	float elapsedTime;

	int maxCheese;
	int numCheese;

	sf::FloatRect playableArea;
	GameObjectPool* cheesePool;
	std::vector<APoolable*> activeCheeseList;
};