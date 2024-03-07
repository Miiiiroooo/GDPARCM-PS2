#include "InteractiveLoadingChecker.h"
#include "../../Scenes/AScene.h"
#include "../../Managers/SceneManager.h"
#include "../../Managers/GameObjectManager.h"

InteractiveLoadingChecker::InteractiveLoadingChecker(LoadingScreenUI* loadingScreenUI) 
	: AComponent("InteractiveLoadingChecker", EComponentTypes::Script), loadingScreenUI(loadingScreenUI)
{
	elapsedTime = 0.f;
}

InteractiveLoadingChecker::~InteractiveLoadingChecker()
{

}

void InteractiveLoadingChecker::Perform()
{
	elapsedTime += deltaTime.asSeconds();
	if (elapsedTime > 1.f)
	{
		elapsedTime = 0.f;
		loadingScreenUI->UpdateLoadingText();
	}

	//AScene* sceneBeingLoaded = SceneManager::GetInstance()->GetActiveScene();

	//if (sceneBeingLoaded->IsAlreadyLoaded())
	//{
	//	AGameObject* parent = this->GetOwner();

	//	GameObjectManager::GetInstance()->DeleteObjectByName(parent->GetName());

	//	// transition logic
	//}
}