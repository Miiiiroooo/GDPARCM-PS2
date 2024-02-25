#pragma once
#include <string>
#include <SFML/Graphics.hpp>
#include "EComponentTypes.h"

class AGameObject;

class AComponent
{
// methods
public:
	AComponent(std::string name, EComponentTypes type);
	virtual ~AComponent();

	void AttachOwner(AGameObject* owner);
	void DetachOwner();
	AGameObject* GetOwner();
	EComponentTypes GetType();
	std::string GetName();

	void SetDeltaTime(sf::Time deltaTime);
	virtual void Perform() = 0;


// attributes
protected:
	AGameObject* owner;
	EComponentTypes type;
	std::string name;
	sf::Time deltaTime;
};

