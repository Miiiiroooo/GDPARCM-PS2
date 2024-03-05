#include "MouseObject.h"
#include "../Components/Animation/AnimationController.h"
#include "../Components/Input/MouseController.h"
#include "../Components/Scripts/MouseScript.h"
#include "../Components/Renderer.h"
#include "../Physics/Collider.h"
#include "../Game.h"

MouseObject::MouseObject() : AGameObject("MousePlayer")
{

}

MouseObject::~MouseObject()
{

}

void MouseObject::Initialize()
{
	this->tag = EObjectTags::Player;
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

	Collider* mouseCollider = new Collider("MouseCollider");
	//mouseCollider->SetLocalBounds(); // figure out way to access sprite
	mouseCollider->SetCollisionListener(this);
	this->AttachComponent(mouseCollider);
}

void MouseObject::OnCollisionEnter(AGameObject* collidedObj)
{
	switch (collidedObj->Tag)
	{
		case EObjectTags::Cheese:
			break;
		case EObjectTags::Enemy:
			break;
		default:
			break;
	}
}

void MouseObject::OnCollisionExit(AGameObject* collidedObj)
{

}