#include "InteractiveLoadingScreen.h"
#include "../Game.h"
#include "../Components/Scripts/InteractiveLoadingChecker.h"
#include "../GameObjects/FPSCounter.h"
#include "../GameObjects/EmptyGameObject.h"
#include "../GameObjects/MouseObject.h"
#include "../GameObjects/PlayableArea.h"
#include "../Components/Scripts/CheeseSpawnerScript.h"
#include "../Components/Scripts/CatSpawnerScript.h"
#include "../UI/LoadingScreenUI.h"

InteractiveLoadingScreen::InteractiveLoadingScreen() : AGameObject("InteractiveLoadingScreen")
{

}

InteractiveLoadingScreen::~InteractiveLoadingScreen()
{

}

void InteractiveLoadingScreen::Initialize()
{
	sf::FloatRect rect = sf::FloatRect(0, 120, Game::WINDOW_WIDTH, Game::WINDOW_HEIGHT - 120 * 2);  

	// initialize minigame objects
	PlayableArea* area = new PlayableArea(rect);
	this->AttachChild(area);

	EmptyGameObject* cheeseSpawner = new EmptyGameObject("CheeseSpawner");
	this->AttachChild(cheeseSpawner);

	CheeseSpawnerScript* cheeseSpawnerScript = new CheeseSpawnerScript(5, rect);
	cheeseSpawner->AttachComponent(cheeseSpawnerScript);

	MouseObject* mouse = new MouseObject(rect);
	this->AttachChild(mouse);

	EmptyGameObject* catSpawner = new EmptyGameObject("CatSpawner");
	this->AttachChild(catSpawner);

	CatSpawnerScript* catSpawnerScript = new CatSpawnerScript(7, rect, mouse);
	catSpawner->AttachComponent(catSpawnerScript);

	// initialize UI objects
	FPSCounter* fpsCounter = new FPSCounter();
	this->AttachChild(fpsCounter);

	LoadingScreenUI* loadingScreenUI = new LoadingScreenUI();
	this->AttachChild(loadingScreenUI);

	// attach loading screen logic 
	InteractiveLoadingChecker* script = new InteractiveLoadingChecker(loadingScreenUI);
	this->AttachComponent(script); 
}