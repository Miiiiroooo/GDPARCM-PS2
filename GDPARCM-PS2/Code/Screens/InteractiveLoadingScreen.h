#pragma once
#include "../GameObjects/AGameObject.h"
#include "../Components/Scripts/LoadingScreenManager.h"


class InteractiveLoadingScreen : public AGameObject
{
public:
	InteractiveLoadingScreen();
	~InteractiveLoadingScreen();

	void Initialize() override;
	LoadingScreenManager* GetManager();


private:
	LoadingScreenManager* manager;
};