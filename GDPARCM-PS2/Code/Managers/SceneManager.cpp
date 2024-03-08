#include "SceneManager.h"
#include "ApplicationManager.h"

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
	storedScenes[scene->GetSceneName()] = scene;
}

void SceneManager::LoadScene(std::string sceneName)
{
	toLoadScene = NULL;
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

		AScene* scene = storedScenes[toLoadSceneName];
		if (!scene->NeedsLoadingScreen())
		{
			activeScene = scene;  
			activeScene->OnLoadResources(); 
			activeScene->OnLoadObjects();
		}
		else
		{
			activeScene = NULL;

			toLoadScene = scene;
			toLoadScene->OnLoadResources();
			toLoadScene->OnLoadObjects(); 

			if (loadingScene == NULL)
			{
				loadingScene = new LoadingScene();
			}
			loadingScene->OnLoadResources();
			loadingScene->OnLoadObjects(); 

			ApplicationManager::GetInstance()->UpdateGameState(EGameStates::Loading);
		}
	}

	if (toLoadScene != NULL && toLoadScene->IsAlreadyLoaded())
	{
		loadingScene->OnUnloadObjects();
		loadingScene->OnUnloadResources();

		activeScene = toLoadScene;
		toLoadScene = NULL;

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