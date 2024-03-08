#pragma once
#include "../AGameObject.h"

class IrisFadeObject : public AGameObject
{
public:
	IrisFadeObject(AGameObject* mouse);
	~IrisFadeObject();

	void Initialize() override;


private:
	sf::Texture* irisTexture;
	AGameObject* mouse;
};