#pragma once
#include "../Components/AComponent.h"
#include "ICollisionListener.h"

class Collider : public AComponent
{
public:
	Collider(std::string name);

	void SetCollisionListener(ICollisionListener* listener);

	void SetChecked(bool flag);
	bool IsChecked();

	bool WillCollide(Collider* another);
	void SetAlreadyCollided(bool flag);
	bool HasAlreadyCollided();
	bool HasAlreadyCollidedWith(AGameObject* collidedObj);

	sf::FloatRect GetGlobalBounds();
	void SetLocalBounds(sf::FloatRect localBounds);
	void CollisionEnter(AGameObject* collidedObj);
	void CollisionExit(AGameObject* collidedObj);

	void Perform() override;


private:
	bool collided = false;
	bool checked = false;

	sf::FloatRect localBounds;
	ICollisionListener* listener;
	std::vector<AGameObject*> collidedObjects;
};

