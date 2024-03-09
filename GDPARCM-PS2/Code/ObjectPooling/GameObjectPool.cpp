#include "GameObjectPool.h"


// constructor and destructor of the GameObjectPool Class
GameObjectPool::GameObjectPool(std::string tag, APoolable* poolableCopy, int poolableSize, AGameObject* parent)
{
	this->tag = tag;
	this->objectCopy = poolableCopy;
	this->maxPoolSize = poolableSize;
	this->parent = parent;
}


GameObjectPool::~GameObjectPool()
{
	delete this->objectCopy;
	this->objectCopy = NULL;
	this->parent = NULL;
}


// public methods of the GameObjectPool Class
void GameObjectPool::Initialize()
{
	for (int i = 0; i < this->maxPoolSize; i++)
	{
		APoolable* poolableObject = this->objectCopy->Clone();

		// instantiate object but disable it first
		if (this->parent != NULL)
		{
			this->parent->AttachChild(poolableObject);
		}
		else
		{
			GameObjectManager::GetInstance()->AddObject(poolableObject);
		}

		poolableObject->SetEnabled(false);
		this->availableObjects.push_back(poolableObject);
	}
}


bool GameObjectPool::HasObjectAvailable(int requestSize)
{
	return requestSize <= this->availableObjects.size();
}


APoolable* GameObjectPool::RequestPoolable()
{
	if (HasObjectAvailable(1))
	{
		size_t availableListSize = this->availableObjects.size();

		APoolable* poolableObject = this->availableObjects[availableListSize - 1];
		this->availableObjects.erase(this->availableObjects.begin() + availableListSize - 1);
		this->usedObjects.push_back(poolableObject);
		SetEnabled(poolableObject, true); 
		//std::cout << "Request Object. Available: " << availableListSize - 1 << "   Used: " << this->usedObjects.size() << std::endl;

		return poolableObject;
	}
	else
	{
		//std::cout << "No more poolable " + this->objectCopy->GetName() + " available! \n";

		return NULL;
	}
}


std::vector<APoolable*> GameObjectPool::RequestPoolableBatch(int size)
{
	std::vector<APoolable*> returnList;

	if (HasObjectAvailable(size))
	{
		for (int i = 0; i < size; i++)
		{
			returnList.push_back(RequestPoolable());
		}
	}
	else
	{
		//std::cout << "Insufficient " + this->objectCopy->GetName() + " available in pool.\nCount is " << this->availableObjects.size() << " while requested is " << size << std::endl;
	}

	return returnList;
}


void GameObjectPool::ReleasePoolable(APoolable* poolableObject)
{
	for (size_t i = 0; i < this->usedObjects.size(); i++)
	{
		if (this->usedObjects[i] == poolableObject)
		{
			this->usedObjects.erase(this->usedObjects.begin() + i);
			this->availableObjects.push_back(poolableObject);
			SetEnabled(poolableObject, false);
		}
	}
}


void GameObjectPool::ReleasePoolableBatch(std::vector<APoolable*> objectList)
{
	for (size_t i = 0; i < objectList.size(); i++)
	{
		ReleasePoolable(objectList[i]);
	}
}


std::string GameObjectPool::GetTag()
{
	return this->tag;
}


// private methods of the GameObjectPool Class
void GameObjectPool::SetEnabled(APoolable* poolableObject, bool flag)
{
	if (flag)
	{
		poolableObject->SetEnabled(true);
		poolableObject->OnActivate();
	}
	else
	{
		poolableObject->SetEnabled(false);
		poolableObject->OnRelease();
	}
}