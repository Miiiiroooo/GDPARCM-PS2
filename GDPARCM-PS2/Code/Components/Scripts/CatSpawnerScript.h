#pragma once
#include "../AComponent.h"
#include "../../ObjectPooling/GameObjectPool.h"

class CatSpawnerScript : public AComponent
{
public:
	CatSpawnerScript(int maxCats, sf::FloatRect area, AGameObject* mouse);
	~CatSpawnerScript();

	void Perform() override;


private:
	const int CHEESE_NUM_TRIGGER = 3;

	int maxCats;
	int numCats;

	sf::FloatRect playableArea;
	GameObjectPool* catPool;
};