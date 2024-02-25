#pragma once
#include "IETThread.h"
#include "AWorkerTask.h"

class ThreadPoolScheduler;

class PoolWorker : public IETThread
{
public:
	PoolWorker(int id, ThreadPoolScheduler* threadPool);
	~PoolWorker();

	int GetID();
	void AssignTask(AWorkerTask* task);

protected:
	void Run() override;


protected:
	int id;
	AWorkerTask* currentTask;
	ThreadPoolScheduler* threadPool;
};