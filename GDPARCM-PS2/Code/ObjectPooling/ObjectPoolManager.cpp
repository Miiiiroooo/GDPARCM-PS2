#include "ObjectPoolManager.h"


// static declarations of the ObjectPoolHolder Class
ObjectPoolManager* ObjectPoolManager::sharedInstance = NULL;
std::string ObjectPoolManager::CHEESE_POOL_TAG = "CheesePool";
std::string ObjectPoolManager::CAT_POOL_TAG = "CatPool";

ObjectPoolManager* ObjectPoolManager::GetInstance()
{
	if (sharedInstance == NULL)
	{
		sharedInstance = new ObjectPoolManager();
	}

	return sharedInstance;
}


// public methods of the ObjectPoolHolder Class
void ObjectPoolManager::RegisterObjectPool(GameObjectPool* pool)
{
	this->poolMap[pool->GetTag()] = pool;
}


void ObjectPoolManager::UnregisterObjectPool(GameObjectPool* pool)
{
	this->poolMap.erase(pool->GetTag());
	delete pool;
}


GameObjectPool* ObjectPoolManager::GetPool(std::string tag)
{
	return this->poolMap[tag];
}