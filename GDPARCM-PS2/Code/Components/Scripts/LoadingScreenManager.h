#pragma once
#include "../AComponent.h"
#include "../../UI/LoadingScreenUI.h"
#include "../../Components/Scripts/MouseScript.h"
#include "../../Components/Scripts/CatSpawnerScript.h"
#include "../../Components/Scripts/CheeseSpawnerScript.h"
#include "../../Components/Scripts/CatScript.h"
#include "../../Scenes/IFinishedSceneLoadListener.h"
#include "../../Scenes/IFinishedSceneTransitionListener.h"
#include "../../GameObjects/LoadingScreen/IrisFadeObject.h"

class LoadingScreenManager : public AComponent, public IFinishedSceneLoadListener
{
public:
	LoadingScreenManager();
	~LoadingScreenManager();

	void SetComponents(LoadingScreenUI* loadingScreenUI, MouseScript* mouseScript, CatSpawnerScript* catSpawner, CheeseSpawnerScript* cheeseSpawner);

	void AddListener(IFinishedSceneTransitionListener* listener);
	void AddListeners(std::vector< IFinishedSceneTransitionListener*> listenersList);

	void OnFinishedSceneLoad() override;
	void Perform() override;

private:
	void OnBeforeSceneLoad();
	void OnAfterSceneLoad();


private:
	LoadingScreenUI* loadingScreenUI;
	MouseScript* mouseScript;
	CatSpawnerScript* catSpawner;
	CheeseSpawnerScript* cheeseSpawner;
	std::vector<CatScript*> catScriptList;
	IrisFadeObject* irisObject;

	std::vector<IFinishedSceneTransitionListener*> listenersList;

	bool sceneHadBeenLoaded;
	float elapsedTime;
	int numCatsOutOfScene;
};