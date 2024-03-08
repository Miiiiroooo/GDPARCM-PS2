#pragma once
#include "../GameObjects/AGameObject.h"

class AScene 
{
public:
	AScene(std::string sceneName, bool needsLoadingScreen);
	~AScene();

	virtual void OnLoadResources() = 0;
	virtual void OnLoadObjects() = 0;
	virtual void OnUnloadResources() = 0;
	virtual void OnUnloadObjects();

	std::string GetSceneName();
	bool NeedsLoadingScreen();
	bool IsAlreadyLoaded();

protected:
	void RegisterObject(AGameObject* object);

	// consider adding list of listeners


protected:
	std::string sceneName;
	bool areResourcesLoaded;
	bool areObjectsLoaded;
	bool needsLoadingScreen;
};