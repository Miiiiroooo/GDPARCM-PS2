#pragma once
#include <unordered_map> 
#include "../Scenes/AScene.h"

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

	AScene* GetActiveScene();
	bool IsGivenSceneLoaded(std::string sceneName);

private:
	SceneManager() {};


public:
	// scene names
	static std::string MAIN_MENU_SCREEN_NAME;
	
private:
	static SceneManager* sharedInstance;

	bool doesSceneNeedToBeLoaded = false;
	std::string toLoadScene;

	SceneTable storedScenes;
	AScene* activeScene;
};

