#include "InteractiveLoadingScreen.h"
#include "../Components/Scripts/InteractiveLoadingChecker.h"
#include "../GameObjects/MouseObject.h"
#include "../GameObjects/FPSCounter.h"

InteractiveLoadingScreen::InteractiveLoadingScreen() : AGameObject("InteractiveLoadingScreen")
{

}

InteractiveLoadingScreen::~InteractiveLoadingScreen()
{

}

void InteractiveLoadingScreen::Initialize()
{
	InteractiveLoadingChecker* script = new InteractiveLoadingChecker();
	this->AttachComponent(script);

	MouseObject* mouse = new MouseObject();
	this->AttachChild(mouse);

	FPSCounter* fpsCounter = new FPSCounter();
	this->AttachChild(fpsCounter);
}