#include "Collider.h"
#include "PhysicsManager.h"

Collider::Collider(std::string name) : AComponent(name, EComponentTypes::Physics)
{

}

void Collider::SetCollisionListener(ICollisionListener* listener)
{
	this->listener = listener;
}

void Collider::SetChecked(bool flag)
{
	this->checked = flag;
}

bool Collider::IsChecked()
{
	return this->checked;
}

bool Collider::WillCollide(Collider* another)
{
	sf::FloatRect A = this->GetGlobalBounds();
	sf::FloatRect B = another->GetGlobalBounds();

	return A.intersects(B);
}

void Collider::SetAlreadyCollided(bool flag)
{
	this->collided = flag;
}

bool Collider::HasAlreadyCollided()
{
	return this->collided;
}

bool Collider::HasAlreadyCollidedWith(AGameObject* collidedObj)
{
	auto objPos = std::find(collidedObjects.begin(), collidedObjects.end(), collidedObj);
	return (objPos != collidedObjects.end());
}

sf::FloatRect Collider::GetGlobalBounds()
{
	return this->GetOwner()->GetGlobalTransform().transformRect(this->localBounds);
}

void Collider::SetLocalBounds(sf::FloatRect localBounds)
{
	this->localBounds = localBounds;
}

void Collider::CollisionEnter(AGameObject* collidedObj)
{
	if (this->listener != NULL)
	{
		this->listener->OnCollisionEnter(collidedObj);
		collidedObjects.push_back(collidedObj);
	}
}

void Collider::CollisionExit(AGameObject* collidedObj)
{
	if (this->listener != NULL)
	{
		this->listener->OnCollisionExit(collidedObj); 

		auto objPos = std::find(collidedObjects.begin(), collidedObjects.end(), collidedObj);
		if (objPos != collidedObjects.end())
		{
			collidedObjects.erase(objPos);
		}
	}
}

void Collider::Perform()
{

}