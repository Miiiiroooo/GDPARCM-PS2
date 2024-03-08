#pragma once

class IFinishedSceneTransitionListener
{
public:
	virtual void OnFinishedSceneLoad() = 0;


protected:
	IFinishedSceneTransitionListener() {};
};