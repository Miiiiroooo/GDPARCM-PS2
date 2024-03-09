#include "FinalScene.h"
#include <fstream>
#include <iostream>
#include "../Managers/SceneManager.h"
#include "../Managers/TextureManager.h"
#include "../Managers/ApplicationManager.h"
#include "../Screens/FinalScreen.h"
#include "../MultiThreading/ThreadPoolScheduler.h"
#include "../MultiThreading/Tasks/LoadAudioTask.h"
#include "../MultiThreading/Tasks/LoadTextureBatchTask.h"
#include "../MultiThreading/Tasks/SortTextureBatchTask.h"


FinalScene::FinalScene() : ToBeLoadedScene(SceneManager::FINAL_SCENE_NAME)
{
	screen = NULL;
	numFinishedResources = 0;
	numFinishedObjects = 0;

	maxAssets = 0;
	intervals = 0;
	maxDigits = 0;
	baseName = "";
	steamedAudioDirectory = "";
}

FinalScene::~FinalScene()
{
	screen = NULL;
}

void FinalScene::OnLoadResources()
{
	std::ifstream inFile;
	inFile.open(STREAMED_ASSETS_DATA_DIR);
	if (!inFile)
	{
		std::cerr << "Unable to open the " << STREAMED_ASSETS_DATA_DIR << "\n" << std::endl;
		return;
	}
	else
	{
		inFile >> maxAssets;
		inFile >> intervals;
		inFile >> maxDigits; 
		inFile >> baseName; 
		inFile >> steamedAudioDirectory; 
	}
	inFile.close();

	LoadAudioTask* audioTask = new LoadAudioTask(steamedAudioDirectory);
	audioTask->AssignFinalScene(this); 
	ThreadPoolScheduler::GetInstance()->ScheduleTask(audioTask);

	int cut = maxAssets / (IETThread::MAX_WORKERS_FOR_LOADING - 1);

	for (int i = 0; i < IETThread::MAX_WORKERS_FOR_LOADING - 1; i++)
	{
		int max = (i != IETThread::MAX_WORKERS_FOR_LOADING - 2) ? cut * (i + 1) : maxAssets;
		LoadTextureBatchTask* textureTask1 = new LoadTextureBatchTask(i * cut, max, intervals, maxDigits, baseName); 
		textureTask1->AssignFinalScene(this); 
		ThreadPoolScheduler::GetInstance()->ScheduleTask(textureTask1); 
	}
}

void FinalScene::OnLoadObjects()
{
	
}

void FinalScene::OnUnloadResources()
{

}

void FinalScene::OnFinishedSceneTransition()
{
	screen->GetVideoHandler()->OnFinishedSceneTransition();
	screen->Enabled = true;
}

void FinalScene::OnFinishedLoadingResources()
{
	numFinishedResources++;

	if (numFinishedResources == IETThread::MAX_WORKERS_FOR_LOADING)
	{
		areResourcesLoaded = true;

		screen = new FinalScreen(); 
		screen->Enabled = false;
		this->RegisterObject(screen); 

		int cut = maxAssets / IETThread::MAX_WORKERS_FOR_LOADING;

		for (int i = 0; i < IETThread::MAX_WORKERS_FOR_LOADING; i++)
		{
			int max = (i != IETThread::MAX_WORKERS_FOR_LOADING - 1) ? cut * (i + 1) : maxAssets;
			SortTextureBatchTask* sortTask = new SortTextureBatchTask(i, i * cut, max, intervals, maxDigits, baseName);
			sortTask->AssignFinalScene(this);
			sortTask->AssignFinalScreen(screen);
			ThreadPoolScheduler::GetInstance()->ScheduleTask(sortTask);
		}
	}
}

void FinalScene::OnFinishedLoadingObjects()
{
	numFinishedObjects++;

	if (numFinishedObjects == IETThread::MAX_WORKERS_FOR_LOADING) 
	{
		areObjectsLoaded = true; 

		for (auto& listener : listenersList) 
		{
			listener->OnFinishedSceneLoad(); 
		}

		ApplicationManager::GetInstance()->UpdateGameState(EGameStates::Transitioning); 
	}
}

void FinalScene::AssignLoadingScene(LoadingScene* loadingScene)
{
	ToBeLoadedScene::AssignLoadingScene(loadingScene);

	LoadingScreenManager* manager = loadingScene->GetManager();
	AddListener(manager);
	manager->AddListener(this);
}