#pragma once
#include "AScene.h"
#include "IFinishedSceneTransitionListener.h"

class FinalScene : public AScene, public IFinishedSceneTransitionListener
{
public:
	FinalScene();
	~FinalScene();

	void OnLoadResources() override;
	void OnLoadObjects() override;
	void OnUnloadResources() override;
	void OnFinishedSceneTransition() override;

	void OnFinishedLoading();


private:
	const std::string STREAMED_ASSETS_DATA_DIR = "Media/StreamedAssetsData.txt";
	const int MAX_WORKERS_FOR_LOADING = 3;
	int numFinished;

	AGameObject* screen;
};