#pragma once

#include <SFML/Graphics.hpp>

class Game : private sf::NonCopyable
{
public:
	static Game* GetInstance();

	void Initialize();
	void Run();
	int GetFPS();
	float GetCurrentGameTime();

private:
	Game();

	void ProcessInputs();
	void Update(sf::Time);
	void Render();
	

public:
	static Game* sharedInstance;
	static const int WINDOW_WIDTH = 1920;
	static const int WINDOW_HEIGHT = 1080;
	static const int FRAME_RATE = 60;
	static const sf::Time TIME_PER_FRAME;

private:
	float FPS;
	float realtimeSinceStartUp;

	sf::RenderWindow window;
};

