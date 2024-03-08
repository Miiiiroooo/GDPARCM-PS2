#pragma once
#include <SFML/Graphics.hpp>
#include "../Enums/EGameStates.h"

class ApplicationManager : public sf::NonCopyable
{
public:
	static ApplicationManager* GetInstance();
	void Initialize(sf::RenderWindow* targetWindow);
	void ApplicationQuit();

	void UpdateGameState(EGameStates newState);
	EGameStates GetCurrentGameState();

	/*void PauseApplication();
	void ResumeApplication();
	bool IsPaused();*/

private:
	ApplicationManager() {};


private:
	static ApplicationManager* sharedInstance;
	sf::RenderWindow* window;
	EGameStates state;
};