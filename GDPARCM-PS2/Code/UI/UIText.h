#pragma once
#include "../GameObjects/AGameObject.h"

class UIText : public AGameObject
{
public:
	UIText(std::string name);
	~UIText();

	void Initialize() override;
	void SetText(std::string text);
	sf::Text* GetText();
	std::string GetTextString();
	void SetSize(unsigned int size);


private:
	sf::Text* text;
};