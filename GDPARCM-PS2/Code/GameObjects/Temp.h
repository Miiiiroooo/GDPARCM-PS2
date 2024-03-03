#pragma once
#include "AGameObject.h"

class Temp : public AGameObject
{
public:
	Temp(int num);
	~Temp();
	void Initialize() override;

private:
	int num;
};

