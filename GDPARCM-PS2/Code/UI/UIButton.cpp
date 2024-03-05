#include "UIButton.h"
#include "../Components/Input/UIButtonInputController.h"

// constructor and destructor of the UIButton Class
UIButton::UIButton(std::string name, sf::Texture* normalTexture, sf::Texture* pressedTexture) 
	: AGameObject(name), normalTexture(normalTexture), pressedTexture(pressedTexture), listener(NULL)
{
	
}

UIButton::~UIButton()
{
	AGameObject::~AGameObject();
}


// public methods of the UIButton Class
void UIButton::Initialize()
{
	this->sprite = new sf::Sprite();
	sprite->setTexture(*this->normalTexture);
	sf::Vector2u textureSize = sprite->getTexture()->getSize();
	sprite->setOrigin(textureSize.x / 2, textureSize.y / 2);

	Renderer* renderer = new Renderer("Button");
	renderer->AssignDrawable(sprite);
	this->AttachComponent(renderer);
}

void UIButton::SetButtonListener(IButtonListener* listener)
{
	// assign input controller 
	this->listener = listener;
	UIButtonInputController* inputController = new UIButtonInputController(name + "_InputController", this->listener);  
	this->AttachComponent(inputController);
}

void UIButton::ChangeButtonToNormal()
{
	this->sprite->setTexture(*this->normalTexture);
}

void UIButton::ChangeButtonToPressed()
{
	this->sprite->setTexture(*this->pressedTexture);
}

sf::FloatRect UIButton::GetLocalBounds()
{
	return this->sprite->getLocalBounds();
}

sf::FloatRect UIButton::GetGlobalBounds()
{
	sf::FloatRect bounds = this->sprite->getGlobalBounds();
	bounds = this->GetGlobalTransform().transformRect(bounds);
	return bounds;
}