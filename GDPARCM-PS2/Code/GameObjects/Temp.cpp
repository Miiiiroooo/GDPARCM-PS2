#include "Temp.h"
#include "../Managers/TextureManager.h"
#include <iostream>

Temp::Temp(int num, std::string key, int x, int y) : AGameObject("temp"), num(num), key(key), x(x), y(y)
{
	
}

Temp::~Temp()
{

}

void Temp::Initialize()
{
	sf::Texture* texture = TextureManager::GetInstance()->GetTexture(key + std::to_string(num + 1));
	this->sprite = new sf::Sprite();
	this->sprite->setTexture(*texture);
	this->sprite->setScale(4, 4);

	this->SetGlobalPosition(num * 16 * 4, y); 

	std::cout << this->GetGlobalPosition().x << " " << this->GetGlobalPosition().y << " " << this->sprite->getPosition().x << " " << this->sprite->getPosition().y << "\n";

	Renderer* renderer = new Renderer(name);
	renderer->AssignDrawable(sprite);
	this->AttachComponent(renderer);
}
