#pragma once
#include "AGameObject.h"
#include "../Physics/ICollisionListener.h"

class MouseObject : public AGameObject, public ICollisionListener
{
public:
	MouseObject();
	~MouseObject();

	void Initialize() override;
	void OnCollisionEnter(AGameObject* collidedObj) override;
	void OnCollisionExit(AGameObject* collidedObj) override;
};

