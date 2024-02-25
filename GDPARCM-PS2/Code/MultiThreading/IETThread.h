#pragma once
#include <thread>
#include <chrono>

class IETThread
{
public:
	IETThread();
	virtual ~IETThread();

	void StartThread();
	static void Sleep(int ms);

protected:
	virtual void Run() = 0;
};