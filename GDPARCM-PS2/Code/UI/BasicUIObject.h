#pragma once
#include "../GameObjects/AGameObject.h"

// UI Object only for displaying a sprite and does not require more components other than the Renderer component
class BasicUIObject : public AGameObject
{
public:
	BasicUIObject(std::string name);
	BasicUIObject(std::string name, std::string textureKey, float scaleValue);
	~BasicUIObject();

	void Initialize() override;


private:
	std::string textureKey;
	float scaleValue;
};

