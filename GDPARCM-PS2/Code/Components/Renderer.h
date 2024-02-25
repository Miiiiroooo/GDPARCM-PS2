#pragma once

#include "AComponent.h"

class Renderer : public AComponent
{
// methods
public:
	Renderer(std::string name);
	~Renderer();

	void AssignTargetWindow(sf::RenderWindow* window);
	void AssignDrawable(sf::Drawable* drawable);
	void SetRenderStates(sf::RenderStates renderStates);

	void Perform() override;


// attributes
private:
	sf::RenderWindow* targetWindow;
	sf::Drawable* drawable;
	sf::RenderStates renderStates;
};

