#include "InteractiveLoadingChecker.h"
#include "../../Scenes/AScene.h"
#include "../../Managers/SceneManager.h"
#include "../../Managers/GameObjectManager.h"

InteractiveLoadingChecker::InteractiveLoadingChecker() : AComponent("InteractiveLoadingChecker", EComponentTypes::Script)
{

}

InteractiveLoadingChecker::~InteractiveLoadingChecker()
{

}

void InteractiveLoadingChecker::Perform()
{
	AScene* sceneBeingLoaded = SceneManager::GetInstance()->GetActiveScene();

	if (sceneBeingLoaded->IsAlreadyLoaded())
	{
		AGameObject* parent = this->GetOwner();

		GameObjectManager::GetInstance()->DeleteObjectByName(parent->GetName());

		// transition logic
	}
}