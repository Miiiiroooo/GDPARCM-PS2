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
	/*sf::Texture* texture = TextureManager::GetInstance()->GetTexture(key + std::to_string(num + 1));
	this->sprite = new sf::Sprite();
	this->sprite->setTexture(*texture);
	this->sprite->setScale(8, 8);*/

	sf::RectangleShape recta = sf::RectangleShape(sf::Vector2f(100, 100));
	recta.setOrigin(50, 50);
	recta.setPosition(50, 50);
	recta.setFillColor(sf::Color::White);
	recta.setOutlineThickness(0);

	sf::CircleShape cir = sf::CircleShape(25);
	cir.setOrigin(25, 25);
	cir.setPosition(50, 50);
	cir.setFillColor(sf::Color::Magenta);
	cir.setOutlineThickness(0);

	sf::RenderTexture tex = sf::RenderTexture();
	tex.create(100, 100);
	tex.draw(recta);
	tex.draw(cir);
	tex.display();

	sf::Image img = tex.getTexture().copyToImage();
	img.createMaskFromColor(sf::Color::Magenta);

	sf::Texture* newTex = new sf::Texture();
	newTex->loadFromImage(img);

	sprite = new sf::Sprite();
	sprite->setTexture(*newTex);


	this->SetGlobalPosition(x, y); 

	Renderer* renderer = new Renderer(name);
	renderer->AssignDrawable(sprite);
	this->AttachComponent(renderer);
}
