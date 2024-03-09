#include "LoadingScene.h"
#include "../Managers/GameObjectManager.h"
#include "../Physics/PhysicsManager.h"

LoadingScene::LoadingScene() : AScene("LoadingScene", false)
{
	loadingScreen = NULL;
}

LoadingScene::~LoadingScene()
{

}

void LoadingScene::OnLoadResources()
{
	areResourcesLoaded = true;
}

void LoadingScene::OnLoadObjects()
{
	loadingScreen = new InteractiveLoadingScreen();
	this->RegisterObject(loadingScreen);

	manager = loadingScreen->GetManager();
	manager->AddListener(this);

	areObjectsLoaded = true;
}

void LoadingScene::OnUnloadResources()
{
	areResourcesLoaded = false;
}

void LoadingScene::OnUnloadObjects()
{
	GameObjectManager::GetInstance()->DeleteObject(loadingScreen);
	PhysicsManager::GetInstance()->UntrackAllObjects();
	loadingScreen = NULL;

	areObjectsLoaded = false;
}

void LoadingScene::OnFinishedSceneTransition()
{
	isFinishedTransitioning = true;
}

LoadingScreenManager* LoadingScene::GetManager()
{
	return manager;
}

bool LoadingScene::IsFinishedTransitioning()
{
	return isFinishedTransitioning;
}

void LoadingScene::CleanupAfterLoading()
{
	loadingScreen = NULL;
	manager = NULL;
}