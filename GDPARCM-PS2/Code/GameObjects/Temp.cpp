#include "Temp.h"
#include "../Managers/TextureManager.h"

Temp::Temp(int num) : AGameObject("temp"), num(num)
{

}

Temp::~Temp()
{

}

void Temp::Initialize()
{
	sf::Texture* texture = TextureManager::GetInstance()->GetTexture("CatIdle" + std::to_string(num + 1));
	this->sprite = new sf::Sprite();
	this->sprite->setTexture(*texture);
	this->sprite->setScale(4, 4);

	this->SetGlobalPosition(0, num * 16 * 4); 

	Renderer* renderer = new Renderer(name);
	renderer->AssignDrawable(sprite);
	this->AttachComponent(renderer);
}
