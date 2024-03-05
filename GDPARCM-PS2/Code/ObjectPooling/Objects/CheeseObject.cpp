#include "CheeseObject.h"
#include "../../Managers/TextureManager.h"
#include "../../Components/Renderer.h"
#include "../../Physics/PhysicsManager.h"

CheeseObject::CheeseObject(int id) : APoolable("CheeseObj_" + id), id(id)
{

}

CheeseObject::~CheeseObject()
{

}

void CheeseObject::Initialize()
{
	this->sprite = new sf::Sprite();
	this->sprite->setTexture(*TextureManager::GetInstance()->GetTexture("Cheese"));
	sf::Vector2u textureSize = sprite->getTexture()->getSize();
	this->sprite->setOrigin((float)textureSize.x / 2, (float)textureSize.y / 2);
	this->sprite->setScale(4.f, 4.f);

	Renderer* renderer = new Renderer("CheeseRenderer");
	renderer->AssignDrawable(sprite);
	this->AttachComponent(renderer);

	cheeseCollider = new Collider("CheeseCollider_" + id);
	cheeseCollider->SetLocalBounds(sprite->getGlobalBounds()); 
	this->AttachComponent(cheeseCollider); 
}

void CheeseObject::OnActivate()
{
	PhysicsManager::GetInstance()->TrackObject(cheeseCollider);
}

void CheeseObject::OnRelease()
{
	PhysicsManager::GetInstance()->UntrackObject(cheeseCollider);
}

APoolable* CheeseObject::Clone()
{
	APoolable* copyObj = new CheeseObject(id + 1);
	return copyObj;
}