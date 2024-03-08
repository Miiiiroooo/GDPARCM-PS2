#pragma once
#include "IETThread.h"
#include "PoolWorker.h"
#include <unordered_map>
#include <queue>
#include <string>
#include <SFML/Graphics.hpp>


class ThreadPoolScheduler : public IETThread, sf::NonCopyable
{
public:
	static ThreadPoolScheduler* GetInstance();
	~ThreadPoolScheduler();

	void Initialize();
	void StartScheduler();
	void StopScheduler();
	void ScheduleTask(AWorkerTask* task);
	void OnFinishedWorker(int id);

private:
	ThreadPoolScheduler() {};
	void Run() override;


private:
	static ThreadPoolScheduler* sharedInstance;

	std::string name;
	int maxWorkers;
	bool isRunning;

	std::unordered_map<int, PoolWorker*> activeThreads;
	std::queue<PoolWorker*> inactiveThreads;
	std::queue<AWorkerTask*> pendingTasks; 
};