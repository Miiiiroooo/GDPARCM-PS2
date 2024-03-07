#include "FPSCounter.h"
#include "../Game.h"
#include "../Components/Scripts/FPSCounterScript.h"

FPSCounter::FPSCounter() : AGameObject("FPSCounter")
{
	counterDisplay = NULL; 
}

FPSCounter::~FPSCounter()
{
	delete counterDisplay->getFont();
	delete counterDisplay;
	AGameObject::~AGameObject();
}

void FPSCounter::Initialize()
{
	// Initialize display
	sf::Font* font = new sf::Font();
	font->loadFromFile("Media/Fonts/Sansation.ttf");

	counterDisplay = new sf::Text();
	counterDisplay->setFont(*font);
	counterDisplay->setPosition(Game::WINDOW_WIDTH - 350.0f, Game::WINDOW_HEIGHT - 80.f);
	counterDisplay->setOutlineColor(sf::Color(1.0f, 1.0f, 1.0f));
	counterDisplay->setOutlineThickness(2.5f);
	counterDisplay->setCharacterSize(75);


	// Initialize and attach components
	FPSCounterScript* counterScript = new FPSCounterScript();
	counterScript->SetCounterDisplay(counterDisplay); 
	this->AttachComponent(counterScript);

	Renderer* render = new Renderer("FPSCounter");
	render->AssignDrawable(counterDisplay); 
	this->AttachComponent(render);
}