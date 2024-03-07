#include "CheeseObject.h"
#include "../../Managers/TextureManager.h"
#include "../../Components/Renderer.h"
#include "../../Physics/PhysicsManager.h"

CheeseObject::CheeseObject(int id, CheeseSpawnerScript* spawner) : APoolable("CheeseObj_" + std::to_string(id)), id(id), cheeseCollider(NULL), spawner(spawner)
{
	tag = EObjectTags::Cheese;
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
	this->sprite->setScale(2.f, 2.f);

	Renderer* renderer = new Renderer("CheeseRenderer");
	renderer->AssignDrawable(sprite);
	this->AttachComponent(renderer);

	cheeseCollider = new Collider("CheeseCollider_" + std::to_string(id));
	cheeseCollider->SetLocalBounds(sprite->getGlobalBounds());
	cheeseCollider->SetCollisionListener(this);
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
	APoolable* copyObj = new CheeseObject(id + 1, spawner);
	return copyObj;
}

void CheeseObject::OnCollisionEnter(AGameObject* collidedObj)
{
	if (collidedObj->Tag != EObjectTags::Player)
	{
		return;
	}

	spawner->OnEatCheese(this);
}

void CheeseObject::OnCollisionExit(AGameObject* collidedObj)
{

}