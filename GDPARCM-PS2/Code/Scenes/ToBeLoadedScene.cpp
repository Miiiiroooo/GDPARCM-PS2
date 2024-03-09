#include "ToBeLoadedScene.h"

ToBeLoadedScene::ToBeLoadedScene(std::string name) : AScene(name, true)
{
	loadingScene = NULL;
	listenersList.clear();
}

ToBeLoadedScene::~ToBeLoadedScene()
{

}

void ToBeLoadedScene::AssignLoadingScene(LoadingScene* loadingScene)
{
	this->loadingScene = loadingScene;
}

void ToBeLoadedScene::AddListener(IFinishedSceneLoadListener* listener)
{
	listenersList.push_back(listener);
}

void ToBeLoadedScene::AddListeners(const std::vector<IFinishedSceneLoadListener*>& listenersList)
{
	this->listenersList.insert(this->listenersList.end(), listenersList.begin(), listenersList.end());
}

void ToBeLoadedScene::CleanupAfterLoading()
{
	loadingScene = NULL;
	listenersList.clear();
	listenersList.shrink_to_fit();
}