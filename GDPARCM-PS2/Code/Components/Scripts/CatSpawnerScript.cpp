#include "CatSpawnerScript.h"
#include "../../ObjectPooling/ObjectPoolManager.h"
#include "../../ObjectPooling/Objects/CatObject.h"
#include "../../Managers/ScoreManager.h"

CatSpawnerScript::CatSpawnerScript(int maxCats) : AComponent("CatSpawnerScript", EComponentTypes::Script), maxCats(maxCats), numCats(0)
{
	catPool = NULL;
}

CatSpawnerScript::~CatSpawnerScript()
{
	activeCatScriptsList.clear();
	delete catPool;
}

void CatSpawnerScript::InitializeSpawner(AGameObject* mouse, sf::FloatRect area)
{
	catPool = new GameObjectPool(ObjectPoolManager::CAT_POOL_TAG, new CatObject(0, mouse, area), maxCats, this->GetOwner()); 
	catPool->Initialize(); 
	ObjectPoolManager::GetInstance()->RegisterObjectPool(catPool); 
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

		activeCatScriptsList.push_back(cat->GetScript());
	}
}

std::vector<CatScript*> CatSpawnerScript::GetActiveCatScriptsList()
{
	return activeCatScriptsList;
}