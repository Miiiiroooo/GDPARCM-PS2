#pragma once
#include "../GameObjects/AGameObject.h"

class ICollisionListener
{
public:
	virtual void OnCollisionEnter(AGameObject* collidedObj) = 0;
	virtual void OnCollisionExit(AGameObject* collidedObj) = 0;

protected:
	ICollisionListener() {};
};