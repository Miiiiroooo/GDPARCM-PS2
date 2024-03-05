#pragma once

#include "../GameObjects/AGameObject.h"
#include "IButtonListener.h"

class UIButton : public AGameObject
{
public:
	UIButton(std::string name, sf::Texture* normalTexture, sf::Texture* pressedTexture);
	~UIButton();

	void Initialize() override;
	void ChangeButtonToNormal();
	void ChangeButtonToPressed();
	sf::FloatRect GetLocalBounds();
	sf::FloatRect GetGlobalBounds();
	void SetButtonListener(IButtonListener* listener);


private:
	sf::Texture* normalTexture;
	sf::Texture* pressedTexture;
	IButtonListener* listener;
};