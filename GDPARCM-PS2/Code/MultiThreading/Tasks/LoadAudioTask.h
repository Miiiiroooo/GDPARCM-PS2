#pragma once
#include <string>
#include "AWorkerTask.h"
#include "../../Scenes/FinalScene.h"

class LoadAudioTask : public AWorkerTask
{
public:
	LoadAudioTask();
	~LoadAudioTask();

	void ExecuteTask() override;
	void AssignFinalScene(FinalScene* scene);


private:
	const std::string STREAMED_AUDIO_DIRECTORY = "Media/StreamedAssets/TomAndJerry.mp3";

	FinalScene* scene;
};