#pragma once
#include "../APoolable.h"
#include "../../Physics/Collider.h"

class CheeseObject : public APoolable
{
public:
	CheeseObject(int id);
	~CheeseObject();

	void Initialize() override;
	void OnActivate() override;
	void OnRelease() override;
	APoolable* Clone() override;


private:
	int id;
	Collider* cheeseCollider;
};