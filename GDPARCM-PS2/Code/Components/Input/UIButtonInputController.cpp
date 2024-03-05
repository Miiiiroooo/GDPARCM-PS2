#include "UIButtonInputController.h"
#include "../../UI/UIButton.h"


UIButtonInputController::UIButtonInputController(std::string name, IButtonListener* listener) : GenericInputController(name), buttonListener(listener)
{
	pressed = false;
}

UIButtonInputController::~UIButtonInputController()
{
	AComponent::~AComponent();
}

void UIButtonInputController::Perform()
{
	UIButton* button = (UIButton*)this->GetOwner();

	
	if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left && this->pressed)
	{
		this->pressed = false;
		button->ChangeButtonToNormal();
		this->buttonListener->OnButtonReleased(button);
	}

	if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
	{
		// check if button is within mouse coords
		sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);
		sf::FloatRect bounds = button->GetGlobalBounds();

		/*
		std::cout << "Mouse X: " << mousePos.x << "   Y: " << mousePos.y << std::endl;
		std::cout << "Bounds X: " << bounds.left << "   Y: " << bounds.top << std::endl;
		*/

		if (bounds.contains(mousePos))
		{
			this->pressed = true;
			button->ChangeButtonToPressed();
			this->buttonListener->OnButtonClick(button);
		}
	}
}