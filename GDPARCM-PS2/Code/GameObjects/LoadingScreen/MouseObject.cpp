#include "MouseObject.h"
#include "../../Game.h"
#include "../../Components/Renderer.h"
#include "../../Components/Animation/AnimationController.h"
#include "../../Components/Input/MouseController.h"
#include "../../Components/Scripts/HitBehaviorScript.h"
#include "../../Physics/PhysicsManager.h"

MouseObject::MouseObject(sf::FloatRect area) : AGameObject("MousePlayer"), playableArea(area)
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

	Collider* mouseCollider = new Collider("MouseCollider");
	this->AttachComponent(mouseCollider);
	PhysicsManager::GetInstance()->TrackObject(mouseCollider);

	HitBehaviorScript* hitScript = new HitBehaviorScript("MouseHitScript", renderer, mouseCollider);
	this->AttachComponent(hitScript);

	script = new MouseScript(playableArea, inputController, animController, mouseCollider, hitScript);
	this->AttachComponent(script);   
}

MouseScript* MouseObject::GetScript()
{
	return script;
}
