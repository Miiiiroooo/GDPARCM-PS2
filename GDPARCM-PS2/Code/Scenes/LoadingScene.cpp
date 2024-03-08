#include "LoadingScene.h"
#include "../Managers/GameObjectManager.h"

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

	areObjectsLoaded = true;
}

void LoadingScene::OnUnloadResources()
{
	areResourcesLoaded = false;
}

void LoadingScene::OnUnloadObjects()
{
	GameObjectManager::GetInstance()->DeleteObject(loadingScreen);
	loadingScreen = NULL;

	areObjectsLoaded = false;
}