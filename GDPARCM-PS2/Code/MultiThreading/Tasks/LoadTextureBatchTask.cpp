#include "LoadTextureBatchTask.h"
#include <iostream>
#include "../IETThread.h"
#include "../../Managers/TextureManager.h"

LoadTextureBatchTask::LoadTextureBatchTask(int startingIndex, int max, int multiplier, int maxDigits, std::string baseName)
	: startingIndex(startingIndex), max(max), multiplier(multiplier), maxDigits(maxDigits), baseName(baseName)
{
	scene = NULL;
}

LoadTextureBatchTask::~LoadTextureBatchTask()
{
	scene = NULL;
}

void LoadTextureBatchTask::ExecuteTask()
{
	for (int i = startingIndex; i < max; i++) 
	{
		IETThread::Sleep(50); 

		int aseetNum = i * multiplier + 1;
		std::string num_string = std::to_string(aseetNum);
		int numDigits = num_string.length();
		num_string.insert(0, (size_t)maxDigits - numDigits, '0'); 
		std::string key = baseName + num_string;

		IETThread::textureManagerSem.acquire();
		TextureManager::GetInstance()->LoadStreamedAssets(key);
		IETThread::textureManagerSem.release();
	}

	IETThread::finishedResourcesSem.acquire();
	if (scene != NULL)
	{
		scene->OnFinishedLoadingResources();
	}
	else
	{
		std::cout << "Finished loading assets, but cannot report to scene\n";
	}
	IETThread::finishedResourcesSem.release();

	delete this;
}

void LoadTextureBatchTask::AssignFinalScene(FinalScene* scene)
{
	this->scene = scene;
}