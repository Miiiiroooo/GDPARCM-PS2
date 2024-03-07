#pragma once
#include "../APoolable.h"
#include "../../Physics/Collider.h"
#include "../../Components/Scripts/CatSpawnerScript.h"

class CatObject : public APoolable
{
public:
	CatObject(int id, AGameObject* mouse, sf::FloatRect area);
	~CatObject();

	void Initialize() override;
	void OnActivate() override;
	void OnRelease() override;
	APoolable* Clone() override;
	void RandomSpawn();


private:
	const float WIDTH_RATIO = 1250.f / 1920.f;
	const float HEIGHT_RATIO = 750.f / 1080.f;

	int id;
	AGameObject* mouse;
	Collider* catCollider;
	sf::FloatRect playableArea;
};

