#pragma once

#include "../GameObjects/AGameObject.h"

class APoolable : public AGameObject
{
public:
	APoolable(std::string name);

	//initializes the properties of this object
	virtual void Initialize() = 0; 

	//throws this event when this object has been released back to the pool
	virtual void OnRelease() = 0; 

	//throws this event when this object has been activated from the pool
	virtual void OnActivate() = 0; 

	//provides a copy of the poolable instance. must be implemented per specific class
	virtual APoolable* Clone() = 0; 
};