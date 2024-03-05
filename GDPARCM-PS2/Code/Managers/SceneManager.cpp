#include "SceneManager.h"


// static declarations of the SceneManager Class
std::string SceneManager::MAIN_MENU_SCREEN_NAME = "MainMenuScene";

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
	this->storedScenes[scene->GetSceneName()] = scene;
}

void SceneManager::LoadScene(std::string sceneName)
{
	this->toLoadScene = sceneName;
	this->doesSceneNeedToBeLoaded = true;

	// loading screen
}

void SceneManager::UnloadScene()
{
	if (this->activeScene != NULL)
	{
		this->activeScene->OnUnloadObjects();
		this->activeScene->OnUnloadResources();
	}
}

void SceneManager::CheckSceneToLoad()
{
	if (this->doesSceneNeedToBeLoaded)
	{
		this->UnloadScene();
		this->activeScene = this->storedScenes[this->toLoadScene];
		this->activeScene->OnLoadResources();
		this->activeScene->OnLoadObjects();
		this->doesSceneNeedToBeLoaded = false;

		// loading screen?
	}
}

AScene* SceneManager::GetActiveScene()
{
	return activeScene;
}

bool SceneManager::IsGivenSceneLoaded(std::string sceneName)
{
	return this->activeScene->GetSceneName() == sceneName;
}