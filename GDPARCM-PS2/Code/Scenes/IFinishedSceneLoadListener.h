#pragma once

class IFinishedSceneLoadListener
{
public:
	virtual void OnFinishedSceneLoad() = 0;


protected:
	IFinishedSceneLoadListener() {};
};