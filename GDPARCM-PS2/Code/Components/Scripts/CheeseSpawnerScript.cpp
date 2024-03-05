#include "CheeseSpawnerScript.h"
#include "../../ObjectPooling/ObjectPoolManager.h"
#include "../../ObjectPooling/Objects/CheeseObject.h"

CheeseSpawnerScript::CheeseSpawnerScript(int maxCheese) : AComponent("CheeseSpawnerScript", EComponentTypes::Script), maxCheese(maxCheese), numCheese(0)
{
	cheesePool = new GameObjectPool(ObjectPoolManager::CHEESE_POOL_TAG, new CheeseObject(0), maxCheese, this->GetOwner());
	cheesePool->Initialize();
	ObjectPoolManager::GetInstance()->RegisterObjectPool(cheesePool);

	elapsedTime = 0;
}

CheeseSpawnerScript::~CheeseSpawnerScript()
{
	delete cheesePool;
}

void CheeseSpawnerScript::Perform()
{
	elapsedTime += deltaTime.asSeconds();

	if (elapsedTime > CHEESE_SPAWN_TIME * std::pow(INCREASED_SPAWN_DELAY, numCheese) && numCheese != maxCheese)
	{
		numCheese++;
		APoolable* cheese = cheesePool->RequestPoolable();

		float randX = rand() % (int)(traversableArea.width - traversableArea.left) + traversableArea.left;
		float randY = rand() % (int)(traversableArea.height - traversableArea.top) + traversableArea.top;
		cheese->SetGlobalPosition(randX, randY);
	}
}