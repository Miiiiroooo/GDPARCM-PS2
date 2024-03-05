#include "UIText.h"
#include "../Managers/FontManager.h"


// constructor and destructor of the UIText Class
UIText::UIText(std::string name) : AGameObject(name)
{
	this->text = new sf::Text();
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
	this->SetSize(40);
	this->SetText("<Using placeholder!>");

	Renderer* renderer = new Renderer("UIText");
	renderer->AssignDrawable(text);
	this->AttachComponent(renderer);
}

void UIText::SetText(std::string text)
{
	this->text->setString(text);
	sf::FloatRect bounds = this->text->getLocalBounds();

	// Align center, you can put other alignments here
	this->text->setOrigin(bounds.width / 2, bounds.height / 2);
}

sf::Text* UIText::GetText()
{
	return this->text;
}

std::string UIText::GetTextString()
{
	return this->text->getString();
}

void UIText::SetSize(unsigned int size)
{
	this->text->setCharacterSize(size);
}