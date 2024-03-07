#pragma once

#include "GameObjectPool.h"

typedef std::unordered_map<std::string, GameObjectPool*> PoolMap;

class ObjectPoolManager : sf::NonCopyable
{
// Methods
public:
	static ObjectPoolManager* GetInstance();

	void RegisterObjectPool(GameObjectPool* pool);
	void UnregisterObjectPool(GameObjectPool* pool);
	GameObjectPool* GetPool(std::string tag);

private:
	ObjectPoolManager() {};


// Attributes
public:
	// pool names
	static std::string CHEESE_POOL_TAG;
	static std::string CAT_POOL_TAG;

private:
	static ObjectPoolManager* sharedInstance;

	PoolMap poolMap;
};