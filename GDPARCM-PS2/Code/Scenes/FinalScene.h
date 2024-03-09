#pragma once
#include "ToBeLoadedScene.h"
#include "IFinishedSceneTransitionListener.h"
#include "../Screens/FinalScreen.h"

class FinalScene : public ToBeLoadedScene, public IFinishedSceneTransitionListener
{
public:
	FinalScene();
	~FinalScene();

	void OnLoadResources() override;
	void OnLoadObjects() override;
	void OnUnloadResources() override;

	void OnFinishedSceneTransition() override;
	void OnFinishedLoadingResources() override;
	void OnFinishedLoadingObjects() override;
	void AssignLoadingScene(LoadingScene* loadingScene) override;


private:
	const std::string STREAMED_ASSETS_DATA_DIR = "Media/StreamedAssetsData.txt";
	int maxAssets;
	int intervals;
	int maxDigits;
	std::string baseName;
	std::string steamedAudioDirectory;

	int numFinishedResources;
	int numFinishedObjects;

	FinalScreen* screen;
};