#pragma once
#include <string>
#include "AWorkerTask.h"
#include "../../Scenes/FinalScene.h"
#include "../../Screens/FinalScreen.h"

class SortTextureBatchTask : public AWorkerTask
{
public:
	SortTextureBatchTask(int id, int startingIndex, int max, int multiplier, int maxDigits, std::string baseName);
	~SortTextureBatchTask();

	void ExecuteTask() override;
	void AssignFinalScene(FinalScene* scene);
	void AssignFinalScreen(FinalScreen* screen);


private:
	static int numFinishedSort;
	static int numWait;

	int startingIndex;
	int max;
	int multiplier;
	int maxDigits;
	std::string baseName;

	int id;
	FinalScene* scene;
	FinalScreen* screen;
};