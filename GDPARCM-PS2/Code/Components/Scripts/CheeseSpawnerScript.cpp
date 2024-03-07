#include "CheeseSpawnerScript.h"
#include "../../ObjectPooling/ObjectPoolManager.h"
#include "../../ObjectPooling/Objects/CheeseObject.h"

CheeseSpawnerScript::CheeseSpawnerScript(int maxCheese, sf::FloatRect area) : AComponent("CheeseSpawnerScript", EComponentTypes::Script), maxCheese(maxCheese), numCheese(0), playableArea(area)
{
	cheesePool = new GameObjectPool(ObjectPoolManager::CHEESE_POOL_TAG, new CheeseObject(0, this), maxCheese, this->GetOwner());
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
	float spawnTimeToCheck = CHEESE_SPAWN_TIME * std::pow(INCREASED_SPAWN_DELAY, numCheese); 

	if (elapsedTime > spawnTimeToCheck && numCheese != maxCheese) 
	{
		elapsedTime = 0;
		numCheese++;
		APoolable* cheese = cheesePool->RequestPoolable();
		sf::FloatRect spriteBounds = cheese->GetSprite()->getGlobalBounds();

		float randX = rand() % (int)(playableArea.width - spriteBounds.width) + playableArea.left + spriteBounds.width / 2;
		float randY = rand() % (int)(playableArea.height - spriteBounds.height) + playableArea.top + spriteBounds.height / 2;
		cheese->SetGlobalPosition(randX, randY);
	}
}

void CheeseSpawnerScript::OnEatCheese(APoolable* cheese)
{
	numCheese--;
	cheesePool->ReleasePoolable(cheese);
}