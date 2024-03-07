#include "CatObject.h"
#include "../../Components/Renderer.h"
#include "../../Components/Scripts/CatScript.h"
#include "../../Components/Animation/AnimationController.h"
#include "../../Physics/PhysicsManager.h"

CatObject::CatObject(int id, AGameObject* mouse, sf::FloatRect area) : APoolable("CatObj_" + std::to_string(id)), id(id), mouse(mouse), catCollider(NULL), playableArea(area)
{
	tag = EObjectTags::Enemy;
}

CatObject::~CatObject()
{

}

void CatObject::Initialize()
{
	Renderer* renderer = new Renderer("CatRenderer_" + std::to_string(id));
	this->AttachComponent(renderer);
	
	AnimationController* animController = new AnimationController("CatAnimController_" + std::to_string(id), renderer);
	this->AttachComponent(animController);
	animController->InitializeAnimations({ "CatIdle", "CatRush" });

	catCollider = new Collider("CatCollider_" + std::to_string(id));
	this->AttachComponent(catCollider);

	CatScript* script = new CatScript(playableArea, animController, catCollider);
	script->SetMouse(mouse);
	this->AttachComponent(script);
}

void CatObject::OnActivate()
{
	PhysicsManager::GetInstance()->TrackObject(catCollider);
}

void CatObject::OnRelease()
{
	PhysicsManager::GetInstance()->UntrackObject(catCollider);
}

APoolable* CatObject::Clone()
{
	APoolable* copyObj = new CatObject(id + 1, mouse, playableArea); 
	return copyObj; 
}

void CatObject::RandomSpawn()
{
	/*sf::FloatRect spriteBounds = GetSprite()->getGlobalBounds(); 
	float randX = rand() % (int)(playableArea.width - spriteBounds.width) + playableArea.left + spriteBounds.width / 2; 
	float randY = rand() % (int)(playableArea.height - spriteBounds.height) + playableArea.top + spriteBounds.height / 2; */
	
	float spawnWidth = WIDTH_RATIO * playableArea.width;
	float spawnHeight = HEIGHT_RATIO * playableArea.height;
	float midX = playableArea.left + playableArea.width / 2;
	float midY = playableArea.top + playableArea.height / 2;

	float randX = rand() % (int)(spawnWidth) - (spawnWidth / 2) + midX;
	float randY = rand() % (int)(spawnHeight) - (spawnHeight / 2) + midY; 
	SetGlobalPosition(randX, randY);
}