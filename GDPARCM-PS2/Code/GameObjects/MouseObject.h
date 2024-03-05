#pragma once
#include "AGameObject.h"

class MouseObject : public AGameObject
{
public:
	MouseObject();
	~MouseObject();

	void Initialize() override;
};

