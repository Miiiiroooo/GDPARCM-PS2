#pragma once
#include "AScene.h"
#include "LoadingScene.h"
#include "IFinishedSceneLoadListener.h"

class ToBeLoadedScene : public AScene
{
public:
	ToBeLoadedScene(std::string name);
	~ToBeLoadedScene();

	virtual void OnFinishedLoadingResources() = 0;
	virtual void OnFinishedLoadingObjects() = 0;

	virtual void AssignLoadingScene(LoadingScene* loadingScene);
	void AddListener(IFinishedSceneLoadListener* listener);
	void AddListeners(const std::vector<IFinishedSceneLoadListener*>& listenersList);
	void CleanupAfterLoading();


protected:
	LoadingScene* loadingScene;
	std::vector<IFinishedSceneLoadListener*> listenersList;
};