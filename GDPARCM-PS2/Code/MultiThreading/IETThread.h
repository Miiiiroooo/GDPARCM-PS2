#pragma once
#include <thread>
#include <chrono>
#include <semaphore>

class IETThread
{
public:
	IETThread();
	virtual ~IETThread();

	void StartThread();
	static void Sleep(int ms);

protected:
	virtual void Run() = 0;


public:
	static const int MAX_WORKERS_FOR_LOADING = 8;
	static std::binary_semaphore textureManagerSem;
	static std::binary_semaphore finishedResourcesSem;
	static std::binary_semaphore numFinishedObjectsLock;
	static std::binary_semaphore numWaitLock;
	static std::counting_semaphore<MAX_WORKERS_FOR_LOADING> waitQueueSem;
};