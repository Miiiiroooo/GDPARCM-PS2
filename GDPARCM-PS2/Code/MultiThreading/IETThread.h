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
	static std::binary_semaphore finishedLoadingSemaphore;
};