#include "ApplicationManager.h"


// static declarations of the ApplicationManager Class
ApplicationManager* ApplicationManager::sharedInstance = NULL;

ApplicationManager* ApplicationManager::GetInstance()
{
	if (sharedInstance == NULL)
		sharedInstance = new ApplicationManager();

	return sharedInstance;
}


// public methods of the ApplicationManager Class
void ApplicationManager::Initialize(sf::RenderWindow* targetWindow)
{
	window = targetWindow;
	state = EGameStates::Running;
}


void ApplicationManager::ApplicationQuit()
{
	window->close();
}

void ApplicationManager::UpdateGameState(EGameStates newState)
{
	state = newState;;
}

EGameStates ApplicationManager::GetCurrentGameState()
{
	return state;
}


//void ApplicationManager::PauseApplication()
//{
//	state = EGameStates::Paused;
//}
//
//
//void ApplicationManager::ResumeApplication()
//{
//	state = EGameStates::Running;
//}
//
//
//bool ApplicationManager::IsPaused()
//{
//	return state == EGameStates::Paused;
//}