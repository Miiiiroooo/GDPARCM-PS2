#pragma once
#include "AScene.h"
#include "IFinishedSceneTransitionListener.h"
#include "../Screens/InteractiveLoadingScreen.h"
#include "../Components/Scripts/LoadingScreenManager.h"

class LoadingScene : public AScene, public IFinishedSceneTransitionListener
{
public:
	LoadingScene();
	~LoadingScene();

	void OnLoadResources() override;
	void OnLoadObjects() override;
	void OnUnloadResources() override;
	void OnUnloadObjects() override;
	void OnFinishedSceneTransition() override;

	LoadingScreenManager* GetManager();
	bool IsFinishedTransitioning();
	void CleanupAfterLoading();


private:
	InteractiveLoadingScreen* loadingScreen;
	LoadingScreenManager* manager;
	bool isFinishedTransitioning;
};