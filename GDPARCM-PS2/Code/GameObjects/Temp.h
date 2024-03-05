#pragma once
#include "AGameObject.h"

class Temp : public AGameObject
{
public:
	Temp(int num, std::string key, int x = 0, int y = 0);
	~Temp();
	void Initialize() override;

private:
	int num;
	int x;
	int y;
	std::string key;
};

