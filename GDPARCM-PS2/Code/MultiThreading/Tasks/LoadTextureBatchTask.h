#pragma once
#include <string>
#include "AWorkerTask.h"
#include "../../Scenes/FinalScene.h"

class LoadTextureBatchTask : public AWorkerTask
{
public:
	LoadTextureBatchTask(int startingIndex, int max, int multiplier, int maxDigits, std::string baseName);
	~LoadTextureBatchTask();

	void ExecuteTask() override;
	void AssignFinalScene(FinalScene* scene);


private:
	int startingIndex;
	int max;
	int multiplier;
	int maxDigits;
	std::string baseName;

	FinalScene* scene;
};

