#include "AScene.h"
#include "../Managers/GameObjectManager.h"
#include "../Physics/PhysicsManager.h"


AScene::AScene(std::string sceneName, bool needsLoadingScreen)
{
	this->sceneName = sceneName;
	this->areResourcesLoaded = false;
	this->areObjectsLoaded = false;
	this->needsLoadingScreen = needsLoadingScreen;
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

bool AScene::NeedsLoadingScreen()
{
	return needsLoadingScreen;
}

bool AScene::IsAlreadyLoaded()
{
	return (areResourcesLoaded && areObjectsLoaded);
}

void AScene::RegisterObject(AGameObject* object)
{
	GameObjectManager::GetInstance()->AddObject(object);
}