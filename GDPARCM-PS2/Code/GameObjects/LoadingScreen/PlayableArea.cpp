#include "PlayableArea.h"
#include "../../Components/Renderer.h"
#include "../../Managers/TextureManager.h"

PlayableArea::PlayableArea(sf::FloatRect rect) : AGameObject("PlayableArea"), rect(rect)
{

}

PlayableArea::~PlayableArea()
{

}

void PlayableArea::Initialize()
{
	sf::Texture* texture = TextureManager::GetInstance()->GetTexture("Floor1");
	texture->setRepeated(true);

	sprite = new sf::Sprite();
	sprite->setTexture(*texture);
	sprite->setOrigin(0, 0);
	sprite->setPosition(rect.left, rect.top);
	sprite->setColor(sf::Color(150, 150, 150));
	sprite->setScale(6, 6);
	sprite->setTextureRect(sf::IntRect(rect.left, rect.top, rect.width / 6, rect.height / 6));

	Renderer* renderer = new Renderer("PlayableAreaRect");
	renderer->AssignDrawable(sprite);
	this->AttachComponent(renderer);
}