#include "LoadAudioTask.h"
#include <iostream>
#include "../../Managers/SFXManager.h"
#include "../IETThread.h"

LoadAudioTask::LoadAudioTask(std::string steamedAudioDirectory) : steamedAudioDirectory(steamedAudioDirectory)
{
	scene = NULL;
}

LoadAudioTask::~LoadAudioTask()
{

}

void LoadAudioTask::ExecuteTask()
{
	SFXManager::GetInstance()->LoadStreamedAudio(steamedAudioDirectory);

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

void LoadAudioTask::AssignFinalScene(FinalScene* scene)
{
	this->scene = scene;
}
