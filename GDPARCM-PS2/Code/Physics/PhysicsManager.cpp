#include "PhysicsManager.h"
#include <iostream>
#include <algorithm>

// static declaration of the PhysicsManager Class
PhysicsManager* PhysicsManager::sharedInstance = NULL;

PhysicsManager* PhysicsManager::GetInstance()
{
	if (sharedInstance == NULL)
	{
		sharedInstance = new PhysicsManager();
	}

	return sharedInstance;
}

// public methods of the PhysicsManager Class
void PhysicsManager::TrackObject(Collider* object)
{
	object->SetAlreadyCollided(false);
	this->trackedObjects.push_back(object);

	//std::cout << "TRACKED: " << object->GetOwner()->GetName() << "  " << trackedObjects.size() << std::endl;
}

void PhysicsManager::UntrackObject(Collider* object)
{
	auto colliderPos = std::find(trackedObjects.begin(), trackedObjects.end(), object);
	if (colliderPos != trackedObjects.end())
	{
		trackedObjects.erase(colliderPos);

		//std::cout << "UNTRACKED: " <<  object->GetOwner()->GetName() << "  " << trackedObjects.size() << std::endl;
	}
}

void PhysicsManager::UntrackAllObjects()
{
	trackedObjects.clear();
}

void PhysicsManager::PhysicsUpdate(float dt)
{
	for (size_t i = 0; i < this->trackedObjects.size(); i++)
	{
		for (size_t j = 0; j < this->trackedObjects.size(); j++)
		{
			Collider* colA = this->trackedObjects[i];
			Collider* colB = this->trackedObjects[j];
			AGameObject* parentA = colA->GetOwner();
			AGameObject* parentB = colB->GetOwner();

			if (colA != colB && parentA->Enabled && parentB->Enabled)
			{
				// check collision between two objects 
				if (colA->WillCollide(colB) && !colA->HasAlreadyCollidedWith(parentB) && !colB->HasAlreadyCollidedWith(parentA))
				{
					/*colA->SetAlreadyCollided(true);
					colB->SetAlreadyCollided(true);*/

					colA->CollisionEnter(parentB);
					colB->CollisionEnter(parentA); 
				}
				else if (!colA->WillCollide(colB) && colA->HasAlreadyCollidedWith(parentB) && colB->HasAlreadyCollidedWith(parentA)) 
				{
					/*colA->SetAlreadyCollided(false); 
					colB->SetAlreadyCollided(false);*/ 

					colA->CollisionExit(parentA); 
					colB->CollisionExit(parentB); 
				}
			}
		}
	}

	for (size_t i = 0; i < this->trackedObjects.size(); i++)
	{
		this->trackedObjects[i]->SetChecked(false);
	}
}