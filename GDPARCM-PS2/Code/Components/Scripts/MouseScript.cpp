#include "MouseScript.h"
#include "../../GameObjects/AGameObject.h"

MouseScript::MouseScript(AGameObject* mouseObj, MouseController* inputController, AnimationController* animController)
	: AComponent("MouseScript", EComponentTypes::Script), mouseObj(mouseObj), inputController(inputController), animController(animController)
{
	isFlipped = false;
}

MouseScript::~MouseScript() 
{

}

void MouseScript::Perform()
{
	MouseController::KeyDictionary keyInputs = inputController->GetHeldKeyInputs();

	// determine direction
	sf::Vector2f movement = sf::Vector2f(0, 0); 
	if (keyInputs[sf::Keyboard::W]) movement.y -= 1; 
	if (keyInputs[sf::Keyboard::S]) movement.y += 1; 
	if (keyInputs[sf::Keyboard::A]) movement.x -= 1; 
	if (keyInputs[sf::Keyboard::D]) movement.x += 1; 

	// normalize movement
	float hypotenuse = std::sqrt(std::pow(movement.x, 2) + std::pow(movement.y, 2)); 
	if (hypotenuse != 0) 
	{
		movement.x /= hypotenuse; 
		movement.y /= hypotenuse; 
		animController->SetBool("isRunning", true); 
	}
	else
	{
		animController->SetBool("isRunning", false); 
	}

	// apply movement
	movement *= MOVE_SPEED; 
	sf::Vector2f currentPos = mouseObj->GetLocalPosition(); 
	currentPos += movement; 
	mouseObj->SetLocalPosition(currentPos.x, currentPos.y); 
	
	// check to flip sprite
	if (keyInputs[sf::Keyboard::A] && !isFlipped) isFlipped = true;
	else if (keyInputs[sf::Keyboard::D] && isFlipped) isFlipped = false;
	animController->FlipSprite(isFlipped);
}