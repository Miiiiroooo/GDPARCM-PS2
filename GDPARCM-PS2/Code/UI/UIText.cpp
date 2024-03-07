#include "UIText.h"
#include "../Managers/FontManager.h"


// constructor and destructor of the UIText Class
UIText::UIText(std::string name) : AGameObject(name)
{
	this->text = new sf::Text();
	this->SetSize(40);
	this->SetText("<Using placeholder!>");

	alignment = EOriginAlignment::Middle_Left;
}

UIText::~UIText()
{
	AGameObject::~AGameObject();
}


// public methods of the UIText Class
void UIText::Initialize()
{
	sf::Font* font = FontManager::GetInstance()->GetFont("default");
	text->setFont(*font);
	text->setFillColor(sf::Color::White);
	text->setOutlineColor(sf::Color::Black);
	text->setOutlineThickness(4.0f);
	text->setOrigin(CalculateOrigin());

	Renderer* renderer = new Renderer("UIText");
	renderer->AssignDrawable(text);
	this->AttachComponent(renderer);
}

void UIText::SetText(std::string text)
{
	this->text->setString(text);
}

sf::Text* UIText::GetText()
{
	return text;
}

std::string UIText::GetTextString()
{
	return text->getString();
}

void UIText::SetSize(unsigned int size)
{
	text->setCharacterSize(size);
}

void UIText::SetFont(sf::Font* font)
{
	text->setFont(*font);
}

void UIText::SetColor(sf::Color color)
{
	text->setFillColor(color);
}

void UIText::SetOriginAlignment(EOriginAlignment alignment)
{
	this->alignment = alignment;
	text->setOrigin(CalculateOrigin());
}

sf::Vector2f UIText::CalculateOrigin()
{
	sf::FloatRect bounds = text->getLocalBounds();

	switch (alignment)
	{
		case EOriginAlignment::Top_Left:
			return sf::Vector2f(bounds.left, bounds.top);

		case EOriginAlignment::Top_Middle:
			return sf::Vector2f(bounds.width / 2, bounds.top);

		case EOriginAlignment::Top_Right:
			return sf::Vector2f(bounds.left + bounds.width, bounds.top);

		case EOriginAlignment::Middle_Left:
			return sf::Vector2f(bounds.left, bounds.height / 2);

		case EOriginAlignment::Middle:
			return sf::Vector2f(bounds.width / 2, bounds.height / 2);

		case EOriginAlignment::Middle_Right:
			return sf::Vector2f(bounds.left + bounds.width, bounds.height / 2);

		case EOriginAlignment::Bottom_Left:
			return sf::Vector2f(bounds.left, bounds.top + bounds.height); 

		case EOriginAlignment::Bottom_Middle:
			return sf::Vector2f(bounds.width / 2, bounds.top + bounds.height); 

		case EOriginAlignment::Bottom_Right:
			return sf::Vector2f(bounds.left + bounds.width, bounds.top + bounds.height); 

		default:
			return sf::Vector2f(bounds.left, bounds.top);
	}
}
