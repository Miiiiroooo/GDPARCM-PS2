#include "ThreadPoolScheduler.h"
#include <iostream>


ThreadPoolScheduler::ThreadPoolScheduler(std::string name) : name(name), maxWorkers(std::thread::hardware_concurrency() * 2), isRunning(false)
{
	for (int i = 0; i < maxWorkers; i++)
	{
		PoolWorker* newWorker = new PoolWorker(i, this);
		inactiveThreads.push(newWorker);
	}
}

ThreadPoolScheduler::~ThreadPoolScheduler()
{
	StopScheduler();

	for (auto& element : activeThreads)
	{
		delete element.second;
		activeThreads.erase(element.first);
	}
	activeThreads.clear();

	while (inactiveThreads.size() > 0)
	{
		PoolWorker* worker = inactiveThreads.front();
		delete worker;
		inactiveThreads.pop();
	}

	while (pendingTasks.size() > 0)
	{
		AWorkerTask* task = pendingTasks.front(); 
		delete task;
		pendingTasks.pop();
	}
}

void ThreadPoolScheduler::StartScheduler()
{
	this->isRunning = true;
}

void ThreadPoolScheduler::StopScheduler()
{
	this->isRunning = false;
}

void ThreadPoolScheduler::ScheduleTask(AWorkerTask* task)
{
	pendingTasks.push(task);
}

void ThreadPoolScheduler::OnFinishedWorker(int id)
{
	if (activeThreads[id] != NULL) 
	{
		PoolWorker* worker = activeThreads[id];
		activeThreads.erase(id);
		inactiveThreads.push(worker);

		/*delete activeThreads[id]; 
		activeThreads.erase(id); 

		PoolWorker* newWorker = new PoolWorker(id, this);
		inactiveThreads.push(newWorker); */
	}
}

// behaves similarly to an update function
void ThreadPoolScheduler::Run()
{
	while (isRunning) 
	{
		//std::cout << "Current Tasks: " << pendingTasks.size() << "  Inactive Threads: " << inactiveThreads.size() << "\n";

		if (pendingTasks.size() > 0) 
		{
			if (inactiveThreads.size() > 0) 
			{
				PoolWorker* worker = inactiveThreads.front(); 
				AWorkerTask* task = pendingTasks.front(); 
				inactiveThreads.pop(); 
				pendingTasks.pop(); 

				worker->AssignTask(task);  
				worker->StartThread();  
				activeThreads[worker->GetID()] = worker; 
			}
		}
	}
}