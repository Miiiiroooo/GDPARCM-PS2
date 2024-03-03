#pragma once
#include "AGameObject.h"

class CatObject : public AGameObject
{
public:
	CatObject(std::string name, AGameObject* mouseObj);
	CatObject(std::string name);
	~CatObject();

	void Initialize() override;


private:
	AGameObject* mouseObj;
	const float scaleValue = 4.f;

	/*const float minDelay = 1.25f;
	const float maxDelay = 2.5f;*/
};

