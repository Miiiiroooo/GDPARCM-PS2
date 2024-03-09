#pragma once
#include <string>
#include "AWorkerTask.h"
#include "../../Scenes/FinalScene.h"

class LoadAudioTask : public AWorkerTask
{
public:
	LoadAudioTask(std::string steamedAudioDirectory);
	~LoadAudioTask();

	void ExecuteTask() override;
	void AssignFinalScene(FinalScene* scene);


private:
	FinalScene* scene;
	std::string steamedAudioDirectory;
};