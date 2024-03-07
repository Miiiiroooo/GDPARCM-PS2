#pragma once
#include "../AComponent.h"
#include "../../UI/LoadingScreenUI.h"

class InteractiveLoadingChecker : public AComponent
{
public:
	InteractiveLoadingChecker(LoadingScreenUI* loadingScreenUI);
	~InteractiveLoadingChecker();

	void Perform() override;


private:
	LoadingScreenUI* loadingScreenUI;
	float elapsedTime;
};