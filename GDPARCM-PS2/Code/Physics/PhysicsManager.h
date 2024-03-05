#pragma once
#include "Collider.h"

class PhysicsManager : sf::NonCopyable
{
public:
	static PhysicsManager* GetInstance();
	~PhysicsManager() {};

	void TrackObject(Collider* object);
	void UntrackObject(Collider* object);
	void UntrackAllObjects();

	void PhysicsUpdate(float dt);

private:
	PhysicsManager() {};


private:
	static PhysicsManager* sharedInstance;
	std::vector<Collider*> trackedObjects;
};

