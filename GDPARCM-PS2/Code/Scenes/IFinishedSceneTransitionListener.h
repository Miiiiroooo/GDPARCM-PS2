#pragma once

class IFinishedSceneTransitionListener
{
public:
	virtual void OnFinishedSceneTransition() = 0;


protected:
	IFinishedSceneTransitionListener() {};
};