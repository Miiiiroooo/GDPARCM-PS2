#include "SortTextureBatchTask.h"
#include "../IETThread.h"
#include "../../Managers/TextureManager.h"
#include <iostream>


int SortTextureBatchTask::numFinishedSort = 0;
int SortTextureBatchTask::numWait = 0;

SortTextureBatchTask::SortTextureBatchTask(int id, int startingIndex, int max, int multiplier, int maxDigits, std::string baseName)
	: id(id), startingIndex(startingIndex), max(max), multiplier(multiplier), maxDigits(maxDigits), baseName(baseName)
{
	scene = NULL;
	screen = NULL;
}

SortTextureBatchTask::~SortTextureBatchTask()
{
	scene = NULL;
	screen = NULL;
}

void SortTextureBatchTask::ExecuteTask()
{
	std::vector<sf::Texture*> texturesList;

	for (int i = startingIndex; i < max; i++)
	{
		IETThread::Sleep(50); 

		int aseetNum = i * multiplier + 1;
		std::string num_string = std::to_string(aseetNum);
		int numDigits = num_string.length();
		num_string.insert(0, (size_t)maxDigits - numDigits, '0');
		std::string key = baseName + num_string;

		texturesList.push_back(TextureManager::GetInstance()->GetTexture(key));
	}


	IETThread::numFinishedObjectsLock.acquire();
	std::cout << "Sorted List -  ID:" << id << "   finish:" << numFinishedSort << "\n";

	while (numFinishedSort != id)
	{
		IETThread::numWaitLock.acquire();
		numWait++;
		std::cout << "In Wait     - ID:" << id << "   wait:" << numWait << "\n";
		IETThread::numWaitLock.release();

		IETThread::numFinishedObjectsLock.release();
		IETThread::waitQueueSem.acquire();
		IETThread::numFinishedObjectsLock.acquire();
	}

	screen->GetVideoHandler()->AddSortedTexturesToList(texturesList);
	scene->OnFinishedLoadingObjects();
	numFinishedSort++;

	std::cout << "Done       - ID:" << id << "   finish:" << numFinishedSort << "   wait:" << numWait << "\n";
	IETThread::numFinishedObjectsLock.release();


	IETThread::numWaitLock.acquire();
	IETThread::waitQueueSem.release(numWait);
	numWait = 0;
	IETThread::numWaitLock.release();
}

void SortTextureBatchTask::AssignFinalScene(FinalScene* scene)
{
	this->scene = scene;
}

void SortTextureBatchTask::AssignFinalScreen(FinalScreen* screen)
{
	this->screen = screen;
}