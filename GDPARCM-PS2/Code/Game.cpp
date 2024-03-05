#include "Game.h"
#include "Managers/GameObjectManager.h"
#include "Managers/TextureManager.h"
#include "Managers/FontManager.h"
#include "Managers/SceneManager.h"
#include "Physics/PhysicsManager.h"
#include "GameObjects/FPSCounter.h"
#include "GameObjects/EmptyGameObject.h"

#include "GameObjects/MouseObject.h"


const sf::Time Game::TIME_PER_FRAME = sf::seconds(1.0f / FRAME_RATE);

Game* Game::sharedInstance = NULL;

Game* Game::GetInstance()
{
	if (sharedInstance == NULL)
	{
		sharedInstance = new Game();
	}

	return sharedInstance;
}

//Game::Game() : window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "GDPARCM")
Game::Game() : window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "GDPARCM", sf::Style::Fullscreen)  
{
	window.setFramerateLimit(FRAME_RATE); 
	//window.setVerticalSyncEnabled(true); 
	srand((unsigned int)time(NULL));

	FPS = 0;
	realtimeSinceStartUp = 0;
}


void Game::Initialize()
{
	// Initialize Managers
	TextureManager::GetInstance()->LoadAllMainAssets();
	FontManager::GetInstance()->LoadAll();

	//SceneManager::getInstance()->registerScene(new MainMenuScene());



	MouseObject* mouse = new MouseObject(); 
	GameObjectManager::GetInstance()->AddObject(mouse); 

	FPSCounter* fpsCounter = new FPSCounter();  
	GameObjectManager::GetInstance()->AddObject(fpsCounter);  
}

// public methods of the Game Class
void Game::Run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;

	while (window.isOpen())
	{
		sf::Time elapsedTime = clock.restart();
		timeSinceLastUpdate += elapsedTime;
		FPS = std::floor(1.f / elapsedTime.asSeconds()); 
		realtimeSinceStartUp += elapsedTime.asSeconds();

		while (timeSinceLastUpdate > TIME_PER_FRAME) 
		{
			timeSinceLastUpdate -= TIME_PER_FRAME; 
			ProcessInputs(); 

			Update(TIME_PER_FRAME); 
			PhysicsManager::GetInstance()->PhysicsUpdate(TIME_PER_FRAME.asSeconds());
		}

		Render();
		//SceneManager::GetInstance()->CheckSceneToLoad();
	}
}

int Game::GetFPS()
{
	return this->FPS;
}

float Game::GetCurrentGameTime()
{
	return this->realtimeSinceStartUp;
}


// private methods of the Game Class
void Game::ProcessInputs()
{
	sf::Event event;

	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed || 
			event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
		{
			window.close();
		}
		else
		{
			GameObjectManager::GetInstance()->ProcessInput(event); 
		}
	}
}


void Game::Update(sf::Time deltaTime)
{
	GameObjectManager::GetInstance()->Update(deltaTime);
}


void Game::Render()
{
	window.clear();
	GameObjectManager::GetInstance()->Draw(&window); 
	window.display();
}