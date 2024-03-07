#include "ScoreManager.h"
#include <fstream>
#include <iostream>

ScoreManager* ScoreManager::sharedInstance = NULL;

ScoreManager* ScoreManager::GetInstance()
{
	if (sharedInstance == NULL)
	{
		sharedInstance = new ScoreManager();
	}

	return sharedInstance;
}

void ScoreManager::Initialize()
{
	cheeseScore = 0;

	std::string fileContent;
	std::ifstream inFile;
	inFile.open("Media/ScoreFile.txt");

	if (!inFile)
	{
		std::cerr << "Cannot open the ScoreFile.txt file" << std::endl;
	}
	else
	{
		while (inFile >> fileContent)
		{
			if (fileContent == "Best Cheese Score:")
			{
				inFile >> fileContent;
				bestCheeseScore = std::stoi(fileContent);
			}
		}
	}

	inFile.close();
}

void ScoreManager::ResetLoadingScreenScore()
{
	cheeseScore = 0;
}

void ScoreManager::AddListener(IScoreListener* listener)
{
	auto listenerPos = std::find(listenersList.begin(), listenersList.end(), listener); 
	if (listenerPos == listenersList.end()) 
	{
		listenersList.push_back(listener); 
	}
}

void ScoreManager::RemoveListener(IScoreListener* listener)
{
	auto listenerPos = std::find(listenersList.begin(), listenersList.end(), listener);
	if (listenerPos != listenersList.end())
	{
		listenersList.erase(listenerPos); 
	}
}

void ScoreManager::UpdateScore(int amount)
{
	cheeseScore += amount;

	if (cheeseScore > bestCheeseScore)
	{
		bestCheeseScore = cheeseScore;
	}

	for (auto& listener : listenersList)
	{
		listener->OnUpdateCheeseScore(cheeseScore);
		listener->OnUpdateBestCheeseScore(bestCheeseScore);
	}
}

int ScoreManager::GetCheeseScore()
{
	return cheeseScore;
}

int ScoreManager::GetBestCheeseScore()
{
	return bestCheeseScore;
}

void ScoreManager::UpdateScoreFile()
{
	std::ofstream outFile;
	outFile.open("Media/ScoreFile.txt");

	if (!outFile)
	{
		std::cerr << "Cannot open the ScoreFile.txt file" << std::endl;
	}
	else
	{
		// revert to the original state of the text file
		outFile << "Best Cheese Score:   " << bestCheeseScore << "\n";
	}

	outFile.close();
}