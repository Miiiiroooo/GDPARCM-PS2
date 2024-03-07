#include "CatSpawnerScript.h"
#include "../../ObjectPooling/ObjectPoolManager.h"
#include "../../ObjectPooling/Objects/CatObject.h"
#include "../../Managers/ScoreManager.h"

CatSpawnerScript::CatSpawnerScript(int maxCats, sf::FloatRect area, AGameObject* mouse) : AComponent("CatSpawnerScript", EComponentTypes::Script), maxCats(maxCats), numCats(0), playableArea(area)
{
	catPool = new GameObjectPool(ObjectPoolManager::CAT_POOL_TAG, new CatObject(0, mouse, area), maxCats, this->GetOwner());
	catPool->Initialize();
	ObjectPoolManager::GetInstance()->RegisterObjectPool(catPool);
}

CatSpawnerScript::~CatSpawnerScript()
{

}

void CatSpawnerScript::Perform()
{
	if (numCats == maxCats)
	{
		return;
	}

	if (ScoreManager::GetInstance()->GetCheeseScore() >= CHEESE_NUM_TRIGGER * (numCats + 1))
	{
		numCats++;
		CatObject* cat = (CatObject*)catPool->RequestPoolable();
		cat->RandomSpawn();
	}
}