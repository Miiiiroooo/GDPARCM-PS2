#include "BasicUIObject.h"
#include "../Managers/TextureManager.h"


BasicUIObject::BasicUIObject(std::string name) : AGameObject(name)
{
	textureKey = "";
	scaleValue = 0;
}

// constructor and destructor of the BasicUIObject Class
BasicUIObject::BasicUIObject(std::string name, std::string textureKey, float scaleValue) : AGameObject(name)
{
	this->textureKey = textureKey;
	this->scaleValue = scaleValue;
}

BasicUIObject::~BasicUIObject()
{

}


// public methods of the BasicUIObject Class
void BasicUIObject::Initialize()
{
	this->sprite = new sf::Sprite();

	if (textureKey != "")
	{
		this->sprite->setTexture(*TextureManager::GetInstance()->GetTexture(textureKey));
		sf::Vector2u textureSize = this->sprite->getTexture()->getSize();
		this->sprite->setOrigin(textureSize.x / 2, textureSize.y / 2);
		this->sprite->setScale(scaleValue, scaleValue);
	}

	// init components
	Renderer* renderer = new Renderer(this->name);
	renderer->AssignDrawable(this->sprite); 
	this->AttachComponent(renderer);
}