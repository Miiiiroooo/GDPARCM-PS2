#include "LoadingScreenManager.h"
#include "../../Managers/ScoreManager.h"

LoadingScreenManager::LoadingScreenManager() : AComponent("LoadingScreenManager", EComponentTypes::Script)
{
	loadingScreenUI = NULL;
	mouseScript = NULL;
	catSpawner = NULL;
	cheeseSpawner = NULL;
	irisObject = NULL;

	sceneHadBeenLoaded = false;
	elapsedTime = 0.f;
	numCatsOutOfScene = 0;
}

LoadingScreenManager::~LoadingScreenManager()
{
}

void LoadingScreenManager::SetComponents(LoadingScreenUI* loadingScreenUI, MouseScript* mouseScript, CatSpawnerScript* catSpawner, CheeseSpawnerScript* cheeseSpawner)
{
	this->loadingScreenUI = loadingScreenUI;
	this->mouseScript = mouseScript;
	this->catSpawner = catSpawner;
	this->cheeseSpawner = cheeseSpawner;
}

void LoadingScreenManager::AddListener(IFinishedSceneTransitionListener* listener)
{
	listenersList.push_back(listener); 
}

void LoadingScreenManager::AddListeners(std::vector< IFinishedSceneTransitionListener*> listenersList) 
{
	this->listenersList.insert(this->listenersList.end(), listenersList.begin(), listenersList.end());
}

void LoadingScreenManager::OnFinishedSceneLoad()
{
	loadingScreenUI->OnFinishedLoading();
	mouseScript->Enabled = false;
	catSpawner->Enabled = false; 
	cheeseSpawner->Enabled = false; 

	cheeseSpawner->ReleaseAllCheese();
	catScriptList = catSpawner->GetActiveCatScriptsList();

	for (auto& cat : catScriptList)
	{
		cat->OnSceneTransition();
	}

	sceneHadBeenLoaded = true;
	elapsedTime = 0.f;

	//ScoreManager::GetInstance()->UpdateScoreFile();
}

void LoadingScreenManager::Perform()
{
	elapsedTime += deltaTime.asSeconds(); 

	if (!sceneHadBeenLoaded)
	{
		OnBeforeSceneLoad();
	}
	else
	{
		OnAfterSceneLoad();
	}
}

void LoadingScreenManager::OnBeforeSceneLoad()
{
	if (elapsedTime > 1.f) 
	{
		elapsedTime = 0.f; 
		loadingScreenUI->UpdateLoadingText(); 
	}
}

void LoadingScreenManager::OnAfterSceneLoad()
{
	if (elapsedTime > 0.35f)
	{
		/*if (numCatsOutOfScene < catScriptList.size())
		{
			CatScript* cat = catScriptList[numCatsOutOfScene]; 
			cat->OnSceneTransitionPounce(); 
			numCatsOutOfScene++;
			elapsedTime = 0.0f;
		}*/
		if (irisObject == NULL)
		{
			irisObject = new IrisFadeObject(mouseScript->GetOwner());
			owner->AttachChild(irisObject);
		}
		else if (irisObject->IsFinishedTransitioning())
		{
			for (auto& listener : listenersList)
			{
				listener->OnFinishedSceneTransition();
			}
		}
	}
}