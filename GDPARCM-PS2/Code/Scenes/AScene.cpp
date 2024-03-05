#include "AScene.h"
#include "../Managers/GameObjectManager.h"
#include "../Physics/PhysicsManager.h"


AScene::AScene(std::string sceneName)
{
	this->sceneName = sceneName;
	this->areResourcesLoaded = false;
	this->areObjectsLoaded = false;
}

AScene::~AScene()
{

}

void AScene::OnUnloadObjects()
{
	GameObjectManager::GetInstance()->DeleteAllObjectsInScene();
	PhysicsManager::GetInstance()->UntrackAllObjects();
}

std::string AScene::GetSceneName()
{
	return this->sceneName;
}

bool AScene::IsAlreadyLoaded()
{
	return (areResourcesLoaded && areObjectsLoaded);
}

void AScene::RegisterObject(AGameObject* object)
{
	GameObjectManager::GetInstance()->AddObject(object);
}