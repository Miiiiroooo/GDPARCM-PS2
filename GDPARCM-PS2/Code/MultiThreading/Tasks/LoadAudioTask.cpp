#include "LoadAudioTask.h"
#include <iostream>
#include "../../Managers/SFXManager.h"
#include "../IETThread.h"

LoadAudioTask::LoadAudioTask()
{
	scene = NULL;
}

LoadAudioTask::~LoadAudioTask()
{

}

void LoadAudioTask::ExecuteTask()
{
	SFXManager::GetInstance()->LoadStreamedAudio(STREAMED_AUDIO_DIRECTORY);

	IETThread::finishedLoadingSemaphore.acquire();
	if (scene != NULL)
	{
		scene->OnFinishedLoading();
	}
	else
	{
		std::cout << "Finished loading assets, but cannot report to scene\n";
	}
	IETThread::finishedLoadingSemaphore.release();

	delete this;
}

void LoadAudioTask::AssignFinalScene(FinalScene* scene)
{
	this->scene = scene;
}
