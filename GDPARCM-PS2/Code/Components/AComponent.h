#pragma once
#include <string>
#include <SFML/Graphics.hpp>
#include "../Enums/EComponentTypes.h"

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
	bool IsEnabled();
	void SetEnabled(bool flag);
	__declspec(property(get = IsEnabled, put = SetEnabled)) bool Enabled;

	void SetDeltaTime(sf::Time deltaTime);
	virtual void Perform() = 0;


// attributes
protected:
	AGameObject* owner;
	EComponentTypes type;
	std::string name;
	sf::Time deltaTime;
	bool componentEnabled;
};

