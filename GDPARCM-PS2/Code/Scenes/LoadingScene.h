#pragma once
#include "AScene.h"
#include "../Screens/InteractiveLoadingScreen.h"

class LoadingScene : public AScene
{
public:
	LoadingScene();
	~LoadingScene();

	void OnLoadResources() override;
	void OnLoadObjects() override;
	void OnUnloadResources() override;
	void OnUnloadObjects() override;


private:
	InteractiveLoadingScreen* loadingScreen;
};