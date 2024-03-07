#pragma once
#include <SFML/Graphics.hpp>
#include "IScoreListener.h"

class ScoreManager : sf::NonCopyable
{
public:
	static ScoreManager* GetInstance();

	void Initialize();
	void ResetLoadingScreenScore();

	void AddListener(IScoreListener* listener);
	void RemoveListener(IScoreListener* listener);

	void UpdateScore(int amount);
	int GetCheeseScore();
	int GetBestCheeseScore();

private:
	ScoreManager() {};
	void UpdateScoreFile();


private:
	static ScoreManager* sharedInstance;

	int bestCheeseScore;
	int cheeseScore;

	std::vector<IScoreListener*> listenersList;
};

