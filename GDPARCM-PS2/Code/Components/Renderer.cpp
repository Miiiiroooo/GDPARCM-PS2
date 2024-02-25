#include "Renderer.h"


// constructor and destructor of the Renderer Class
Renderer::Renderer(std::string name) : AComponent(name, EComponentTypes::Renderer)
{
	this->targetWindow = NULL;
	this->drawable = NULL;
	this->renderStates = sf::RenderStates::Default;
}


Renderer::~Renderer()
{
	//delete this->drawable;
	AComponent::~AComponent();
}


// public methods of the Renderer Class
void Renderer::AssignTargetWindow(sf::RenderWindow* window)
{
	this->targetWindow = window;
}


void Renderer::AssignDrawable(sf::Drawable* drawable)
{
	this->drawable = drawable;
}


void Renderer::SetRenderStates(sf::RenderStates renderStates)
{
	this->renderStates = renderStates;
}


void Renderer::Perform()
{
	if (this->targetWindow == NULL || this->drawable == NULL)
	{
		return;
	}

	this->targetWindow->draw(*this->drawable, this->renderStates);
}