#include "InteractiveLoadingScreen.h"
#include "../Game.h"
#include "../GameObjects/FPSCounter.h"
#include "../GameObjects/EmptyGameObject.h"
#include "../GameObjects/LoadingScreen/PlayableArea.h"
#include "../GameObjects/LoadingScreen/MouseObject.h"
#include "../GameObjects/LoadingScreen/IrisFadeObject.h"
#include "../Components/Scripts/CheeseSpawnerScript.h"
#include "../Components/Scripts/CatSpawnerScript.h"

InteractiveLoadingScreen::InteractiveLoadingScreen() : AGameObject("InteractiveLoadingScreen")
{
	manager = NULL;
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

	MouseObject* mouse = new MouseObject(rect); 
	this->AttachChild(mouse); 

	EmptyGameObject* cheeseSpawner = new EmptyGameObject("CheeseSpawner");
	this->AttachChild(cheeseSpawner);

	CheeseSpawnerScript* cheeseSpawnerScript = new CheeseSpawnerScript(5, rect);
	cheeseSpawner->AttachComponent(cheeseSpawnerScript);
	cheeseSpawnerScript->InitializeSpawner(); 

	EmptyGameObject* catSpawner = new EmptyGameObject("CatSpawner");
	this->AttachChild(catSpawner);

	CatSpawnerScript* catSpawnerScript = new CatSpawnerScript(7);
	catSpawner->AttachComponent(catSpawnerScript);
	catSpawnerScript->InitializeSpawner(mouse, rect); 

	// initialize UI objects
	FPSCounter* fpsCounter = new FPSCounter();
	this->AttachChild(fpsCounter);

	LoadingScreenUI* loadingScreenUI = new LoadingScreenUI();
	this->AttachChild(loadingScreenUI); 

	// attach loading screen logic 
	manager = new LoadingScreenManager(); 
	manager->SetComponents(loadingScreenUI, mouse->GetScript(), catSpawnerScript, cheeseSpawnerScript);
	this->AttachComponent(manager); 
}

LoadingScreenManager* InteractiveLoadingScreen::GetManager()
{
	return manager;
}
