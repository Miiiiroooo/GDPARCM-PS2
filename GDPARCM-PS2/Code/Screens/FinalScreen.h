#pragma once
#include "../GameObjects/AGameObject.h"

class FinalScreen : public AGameObject
{
public:
	FinalScreen();
	~FinalScreen();

	void Initialize() override;
};