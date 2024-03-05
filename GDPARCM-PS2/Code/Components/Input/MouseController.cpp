#include "MouseController.h"

MouseController::MouseController() : GenericInputController("MouseController")
{

}

MouseController::~MouseController()
{

}

void MouseController::Perform()
{
	heldKeyInputs[sf::Keyboard::W] = sf::Keyboard::isKeyPressed(sf::Keyboard::W);
	heldKeyInputs[sf::Keyboard::A] = sf::Keyboard::isKeyPressed(sf::Keyboard::A);
	heldKeyInputs[sf::Keyboard::S] = sf::Keyboard::isKeyPressed(sf::Keyboard::S);
	heldKeyInputs[sf::Keyboard::D] = sf::Keyboard::isKeyPressed(sf::Keyboard::D);
}

MouseController::KeyDictionary& MouseController::GetHeldKeyInputs()
{
	return heldKeyInputs;
}