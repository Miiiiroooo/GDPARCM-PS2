#pragma once
#include "../AComponent.h"
#include "../../ObjectPooling/GameObjectPool.h"
#include "CatScript.h"

class CatSpawnerScript : public AComponent
{
public:
	CatSpawnerScript(int maxCats);
	~CatSpawnerScript();

	void InitializeSpawner(AGameObject* mouse, sf::FloatRect area);
	void Perform() override;
	std::vector<CatScript*> GetActiveCatScriptsList();


private:
	const int CHEESE_NUM_TRIGGER = 2;

	int maxCats;
	int numCats;

	GameObjectPool* catPool;
	std::vector<CatScript*> activeCatScriptsList;
};