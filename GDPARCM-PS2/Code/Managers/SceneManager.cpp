#include "SceneManager.h"
#include "ApplicationManager.h"
#include <iostream>

// static declarations of the SceneManager Class
std::string SceneManager::FINAL_SCENE_NAME = "FinalScene";

SceneManager* SceneManager::sharedInstance = NULL;

SceneManager* SceneManager::GetInstance()
{
	if (sharedInstance == NULL)
		sharedInstance = new SceneManager();

	return sharedInstance;
}

// public methods of the SceneManager Class
void SceneManager::RegisterScene(AScene* scene)
{
	storedScenesTable[scene->GetSceneName()] = scene;
}

void SceneManager::LoadScene(std::string sceneName)
{
	toBeLoadedScene = NULL;
	toLoadSceneName = sceneName;
	doesSceneNeedToBeLoaded = true;
}

void SceneManager::UnloadScene()
{
	if (activeScene != NULL)
	{
		activeScene->OnUnloadObjects();
		activeScene->OnUnloadResources();
	}
}

void SceneManager::CheckSceneToLoad()
{
	if (doesSceneNeedToBeLoaded)
	{
		UnloadScene();

		doesSceneNeedToBeLoaded = false;

		AScene* scene = storedScenesTable[toLoadSceneName];
		if (!scene->NeedsLoadingScreen())
		{
			activeScene = scene;  
			activeScene->OnLoadResources(); 
			activeScene->OnLoadObjects();
		}
		else
		{
			activeScene = NULL;

			toBeLoadedScene = (ToBeLoadedScene*)scene;
			toBeLoadedScene->OnLoadResources();
			toBeLoadedScene->OnLoadObjects(); 

			if (loadingScene == NULL)
			{
				loadingScene = new LoadingScene();
			}
			loadingScene->OnLoadResources();
			loadingScene->OnLoadObjects(); 

			toBeLoadedScene->AssignLoadingScene(loadingScene);
			ApplicationManager::GetInstance()->UpdateGameState(EGameStates::Loading);
		}
	}

	if (toBeLoadedScene != NULL && toBeLoadedScene->IsAlreadyLoaded() && loadingScene->IsFinishedTransitioning())
	{
		loadingScene->OnUnloadObjects();
		loadingScene->OnUnloadResources();
		loadingScene->CleanupAfterLoading();

		activeScene = toBeLoadedScene;
		toBeLoadedScene->CleanupAfterLoading();
		toBeLoadedScene = NULL;

		ApplicationManager::GetInstance()->UpdateGameState(EGameStates::Running);
	}
}

std::string SceneManager::GetActiveSceneName()
{
	return activeScene->GetSceneName();
}

bool SceneManager::IsGivenSceneLoaded(std::string sceneName)
{
	return this->activeScene->GetSceneName() == sceneName;
}