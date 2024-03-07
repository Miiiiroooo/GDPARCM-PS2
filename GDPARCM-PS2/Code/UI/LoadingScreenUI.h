#pragma once
#include "../GameObjects/AGameObject.h"
#include "../Managers/IScoreListener.h"
#include "UIText.h"

class LoadingScreenUI : public AGameObject, public IScoreListener
{
public:
	LoadingScreenUI();
	~LoadingScreenUI();

	void Initialize() override;
	void OnUpdateCheeseScore(int score) override;
	void OnUpdateBestCheeseScore(int score) override;
	void OnFinishedLoading();

	void UpdateLoadingText();


private:
	UIText* bestCheeseScoreText;
	UIText* cheeseScoreText;
	UIText* loadingText;

	const int MAX_PERIODS = 4;
	int numPeriods = 0;
};