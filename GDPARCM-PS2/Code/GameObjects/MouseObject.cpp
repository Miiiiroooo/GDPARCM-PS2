#include "MouseObject.h"
#include "../Components/Animation/AnimationController.h"
#include "../Components/Input/MouseController.h"
#include "../Components/Scripts/MouseScript.h"
#include "../Components/Renderer.h"
#include "../Game.h"

MouseObject::MouseObject() : AGameObject("MousePlayer")
{

}

MouseObject::~MouseObject()
{

}

void MouseObject::Initialize()
{
	this->SetGlobalPosition(Game::WINDOW_WIDTH / 2, Game::WINDOW_HEIGHT / 2);

	Renderer* renderer = new Renderer("MouseRenderer");
	this->AttachComponent(renderer); 

	AnimationController* animController = new AnimationController("MouseAnimController", renderer);
	animController->InitializeAnimations({ "MouseIdle" , "MouseRun", "MouseEat" });
	this->AttachComponent(animController); 

	MouseController* inputController = new MouseController(); 
	this->AttachComponent(inputController); 

	MouseScript* script = new MouseScript(this, inputController, animController);  
	this->AttachComponent(script);   
}