#include "LoadingScreenUI.h"
#include "../Game.h"
#include "../Managers/ScoreManager.h"

LoadingScreenUI::LoadingScreenUI() : AGameObject("LoadingScreenUI")
{
	tag = EObjectTags::UI;
}

LoadingScreenUI::~LoadingScreenUI()
{
	ScoreManager::GetInstance()->RemoveListener(this);
}

void LoadingScreenUI::Initialize()
{
	bestCheeseScoreText = new UIText("BestCheeseScoreText");
	bestCheeseScoreText->SetSize(45);
	bestCheeseScoreText->SetText("Best Cheese Score: " + std::to_string(ScoreManager::GetInstance()->GetBestCheeseScore()));
	bestCheeseScoreText->SetGlobalPosition(30.f, 45.f);
	bestCheeseScoreText->SetOriginAlignment(EOriginAlignment::Top_Left);
	bestCheeseScoreText->Enabled = false;
	this->AttachChild(bestCheeseScoreText);

	cheeseScoreText = new UIText("CheeseScoreText");
	cheeseScoreText->SetSize(45);
	cheeseScoreText->SetText("Cheese Score: " + std::to_string(ScoreManager::GetInstance()->GetCheeseScore()));
	cheeseScoreText->SetGlobalPosition(Game::WINDOW_WIDTH - 30.f, 45.f);
	cheeseScoreText->SetOriginAlignment(EOriginAlignment::Top_Right);
	cheeseScoreText->Enabled = false;
	this->AttachChild(cheeseScoreText);

	loadingText = new UIText("LoadingText");
	loadingText->SetSize(75);
	loadingText->SetText("Loading");
	loadingText->SetGlobalPosition(30.f, Game::WINDOW_HEIGHT);
	loadingText->SetOriginAlignment(EOriginAlignment::Bottom_Left);
	this->AttachChild(loadingText);

	ScoreManager::GetInstance()->AddListener(this);
}

void LoadingScreenUI::OnUpdateCheeseScore(int score)
{
	cheeseScoreText->SetText("Cheese Score: " + std::to_string(score)); 

	if (!bestCheeseScoreText->Enabled && !cheeseScoreText->Enabled)
	{
		bestCheeseScoreText->Enabled = true;
		cheeseScoreText->Enabled = true;
	}
}

void LoadingScreenUI::OnUpdateBestCheeseScore(int score)
{
	bestCheeseScoreText->SetText("Best Cheese Score: " + std::to_string(score)); 
}

void LoadingScreenUI::OnFinishedLoading()
{
	loadingText->SetText("LOADING COMPLETE");
	loadingText->SetColor(sf::Color::Green);
}

void LoadingScreenUI::UpdateLoadingText()
{
	numPeriods++;
	if (numPeriods > MAX_PERIODS)
	{
		numPeriods = 0;
	}

	std::string periodsText = "";
	for (int i = 0; i < numPeriods; i++)
	{
		periodsText += ".";
	}

	loadingText->SetText("Loading" + periodsText);
}
