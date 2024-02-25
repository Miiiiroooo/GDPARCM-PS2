#pragma once
#include "IETThread.h"
#include "PoolWorker.h"
#include <unordered_map>
#include <queue>
#include <string>


class ThreadPoolScheduler : public IETThread
{
public:
	ThreadPoolScheduler(std::string name);
	~ThreadPoolScheduler();

	void StartScheduler();
	void StopScheduler();
	void ScheduleTask(AWorkerTask* task);
	void OnFinishedWorker(int id);

private:
	void Run() override;


private:
	std::string name;
	int maxWorkers;
	bool isRunning;

	std::unordered_map<int, PoolWorker*> activeThreads;
	std::queue<PoolWorker*> inactiveThreads;
	std::queue<AWorkerTask*> pendingTasks; 
};