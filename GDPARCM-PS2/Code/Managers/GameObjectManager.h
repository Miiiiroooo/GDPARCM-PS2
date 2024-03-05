#pragma once
#include "../GameObjects/AGameObject.h"
#include <unordered_map>

// Should only contain base game objects (one's with no parents)
class GameObjectManager : sf::NonCopyable
{
public:
	static GameObjectManager* GetInstance();

	// Game-related methods
	void ProcessInput(sf::Event event);
	void Update(sf::Time deltaTime);
	void Draw(sf::RenderWindow* window);

	// Object-related methods
	void AddObject(AGameObject* gameObject);
	AGameObject* FindObjectByName(std::string name);
	void DeleteObject(AGameObject* gameObject);
	void DeleteObjectByName(std::string name);
	std::vector<AGameObject*> GetAllObjects(); 
	int GetActiveObjectsCount();

	void DeleteAllObjectsInScene();


private:
	GameObjectManager() {};
	static GameObjectManager* sharedInstance;

	std::unordered_map<std::string, AGameObject*> gameObjectMap;
	std::vector<AGameObject*> gameObjectList;
};

