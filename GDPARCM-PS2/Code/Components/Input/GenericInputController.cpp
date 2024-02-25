#include "GenericInputController.h"


// constructor and destructor of the GenericInputController Class
GenericInputController::GenericInputController(std::string name) : AComponent(name, EComponentTypes::Input)
{
	
}


GenericInputController::~GenericInputController()
{
	AComponent::~AComponent();
}


// public methods of the GenericInputController Class
void GenericInputController::Perform()
{

}


void GenericInputController::AssignEvent(sf::Event event)
{
	this->event = event;
}