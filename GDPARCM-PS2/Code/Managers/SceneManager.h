#pragma once
#include <unordered_map> 
#include "../Scenes/AScene.h"
#include "../Scenes/LoadingScene.h"

typedef std::unordered_map<std::string, AScene*> SceneTable;
typedef std::vector<std::string> SceneList;

class SceneManager : sf::NonCopyable
{
public:
	static SceneManager* GetInstance();

	void RegisterScene(AScene* scene);
	void LoadScene(std::string sceneName); // notifies manager what to load
	void UnloadScene();
	void CheckSceneToLoad(); // does the loading if there are scenes to load

	std::string GetActiveSceneName();
	bool IsGivenSceneLoaded(std::string sceneName);

private:
	SceneManager() {};


public:
	// scene names
	static std::string FINAL_SCENE_NAME;
	
private:
	static SceneManager* sharedInstance;

	bool doesSceneNeedToBeLoaded = false;
	std::string toLoadSceneName;
	AScene* toLoadScene;

	SceneTable storedScenes;
	AScene* activeScene;
	AScene* loadingScene;
};

