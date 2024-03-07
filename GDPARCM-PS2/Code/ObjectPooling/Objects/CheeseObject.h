#pragma once
#include "../APoolable.h"
#include "../../Physics/Collider.h"
#include "../../Physics/ICollisionListener.h"
#include "../../Components/Scripts/CheeseSpawnerScript.h"

class CheeseObject : public APoolable, ICollisionListener
{
public:
	CheeseObject(int id, CheeseSpawnerScript* spawner);
	~CheeseObject();

	void Initialize() override;
	void OnActivate() override;
	void OnRelease() override;
	APoolable* Clone() override;
	void OnCollisionEnter(AGameObject* collidedObj) override;
	void OnCollisionExit(AGameObject* collidedObj) override;


private:
	int id;
	Collider* cheeseCollider;
	CheeseSpawnerScript* spawner;
};