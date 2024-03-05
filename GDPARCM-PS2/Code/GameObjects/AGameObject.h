#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "../Components/AComponent.h"
#include "../Components/Renderer.h"

class AGameObject
{
public:
	// Constructor-Destructor
	AGameObject(std::string name);
	~AGameObject();

	// Game-related methods
	virtual void Initialize() = 0;
	virtual void ProcessInputs(sf::Event event);
	virtual void Update(sf::Time dt);
	virtual void Draw(sf::RenderWindow* window, sf::RenderStates renderStates); 

	std::string GetName();
	bool IsEnabled();
	void SetEnabled(bool flag);
	__declspec(property(get = IsEnabled, put = SetEnabled)) bool Enabled;

	// SFML-related methods
	sf::Sprite* GetSprite();
	void UpdateSprite(sf::Sprite* newSprite);
	sf::Transformable* GetTransformable();
	sf::Transform GetGlobalTransform();
	void SetLocalPosition(float x, float y);
	void SetGlobalPosition(float x, float y);
	sf::Vector2f GetLocalPosition();
	sf::Vector2f GetGlobalPosition();

	// Inheritance-related methods
	void AttachChild(AGameObject* child);
	void DetachChild(AGameObject* child);
	AGameObject* GetParent();

	// Component-related methods
	void AttachComponent(AComponent* component);
	void DetachComponent(AComponent* component);
	AComponent* FindComponentByName(std::string name);
	AComponent* FindComponentByType(EComponentTypes type, std::string name);
	std::vector<AComponent*> GetComponentsOfType(EComponentTypes type);
	//std::vector<AComponent*> GetComponentsOfTypeRecursive(AComponent::ComponentType type);

private:
	void SetParent(AGameObject* parent);
	//std::vector<AComponent*> GetComponentRecursiveProper(AGameObject* object, AComponent::ComponentType type, std::vector<AComponent*> foundList);


protected:
	std::string name;
	sf::Sprite* sprite;
	sf::Texture* texture;
	sf::Transformable transformable;

	AGameObject* parent;
	std::vector<AGameObject*> childList;
	std::vector<AComponent*> componentList; 

private:
	bool enabled = true;
};

