#pragma once

#include "APoolable.h"
#include "../Managers/GameObjectManager.h"

class GameObjectPool
{
// methods
public:
	GameObjectPool(std::string tag, APoolable* poolableCopy, int poolableSize, AGameObject* parent);
	~GameObjectPool();

	void Initialize();
	bool HasObjectAvailable(int requestSize);
	APoolable* RequestPoolable();
	std::vector<APoolable*> RequestPoolableBatch(int size); 
	void ReleasePoolable(APoolable* poolableObject);
	void ReleasePoolableBatch(std::vector<APoolable*> objectList); 

	std::string GetTag();

private:
	void SetEnabled(APoolable* poolableObject, bool flag);


// attributes
private:
	std::string tag;
	APoolable* objectCopy = NULL;
	AGameObject* parent = NULL;
	int maxPoolSize = 20;
	std::vector<APoolable*> availableObjects;
	std::vector<APoolable*> usedObjects;
};