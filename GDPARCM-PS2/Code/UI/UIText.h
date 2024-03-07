#pragma once
#include "../GameObjects/AGameObject.h"
#include "../Enums/EOriginAlignment.h"

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
	void SetFont(sf::Font* font);
	void SetColor(sf::Color color);
	void SetOriginAlignment(EOriginAlignment alignment);

private:
	sf::Vector2f CalculateOrigin();


private:
	sf::Text* text;
	EOriginAlignment alignment;
};