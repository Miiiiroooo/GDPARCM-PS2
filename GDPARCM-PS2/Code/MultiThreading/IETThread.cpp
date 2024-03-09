#include "IETThread.h"


std::binary_semaphore IETThread::textureManagerSem(1);
std::binary_semaphore IETThread::finishedResourcesSem(1);
std::binary_semaphore IETThread::numFinishedObjectsLock(1);
std::binary_semaphore IETThread::numWaitLock(1);
std::counting_semaphore<IETThread::MAX_WORKERS_FOR_LOADING> IETThread::waitQueueSem(0);

IETThread::IETThread()
{

}

IETThread::~IETThread()
{

}

void IETThread::StartThread()
{
	std::thread(&IETThread::Run, this).detach(); 
}

void IETThread::Sleep(int ms)
{
	std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}