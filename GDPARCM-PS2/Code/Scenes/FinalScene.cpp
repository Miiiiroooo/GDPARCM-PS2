#include "FinalScene.h"
#include <fstream>
#include <iostream>
#include "../Managers/SceneManager.h"
#include "../Managers/ApplicationManager.h"
#include "../Screens/FinalScreen.h"
#include "../MultiThreading/ThreadPoolScheduler.h"
#include "../MultiThreading/Tasks/LoadAudioTask.h"
#include "../MultiThreading/Tasks/LoadTextureBatchTask.h"


FinalScene::FinalScene() : AScene(SceneManager::FINAL_SCENE_NAME, true)
{
	screen = NULL;
	numFinished = 0;
}

FinalScene::~FinalScene()
{

}

void FinalScene::OnLoadResources()
{
	int max, multiplier, maxDigits;
	std::string baseName;
	std::ifstream inFile;
	
	inFile.open(STREAMED_ASSETS_DATA_DIR);
	if (!inFile)
	{
		std::cerr << "Unable to open the " << STREAMED_ASSETS_DATA_DIR << "\n" << std::endl;
		return;
	}
	else
	{
		inFile >> max;
		inFile >> multiplier;
		inFile >> maxDigits;
		inFile >> baseName;
	}

	inFile.close();

	LoadAudioTask* audioTask = new LoadAudioTask();
	audioTask->AssignFinalScene(this); 
	ThreadPoolScheduler::GetInstance()->ScheduleTask(audioTask);

	int half = max / 2;

	LoadTextureBatchTask* textureTask1 = new LoadTextureBatchTask(0, half, multiplier, maxDigits, baseName);
	textureTask1->AssignFinalScene(this);
	ThreadPoolScheduler::GetInstance()->ScheduleTask(textureTask1);

	LoadTextureBatchTask* textureTask2 = new LoadTextureBatchTask(half + 1, max, multiplier, maxDigits, baseName);
	textureTask2->AssignFinalScene(this);
	ThreadPoolScheduler::GetInstance()->ScheduleTask(textureTask2);
}

void FinalScene::OnLoadObjects()
{
	screen = new FinalScreen;
	screen->Enabled = false;
	this->RegisterObject(screen);
}

void FinalScene::OnUnloadResources()
{

}

void FinalScene::OnFinishedSceneTransition()
{
	screen->Enabled = true;
}

void FinalScene::OnFinishedLoading()
{
	numFinished++;

	if (numFinished == MAX_WORKERS_FOR_LOADING)
	{
		ApplicationManager::GetInstance()->UpdateGameState(EGameStates::Transitioning);

		// notify listeners
	}
}