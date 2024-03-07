#include "MouseScript.h"
#include "../../GameObjects/AGameObject.h"
#include "../../Managers/ScoreManager.h"
#include "../../Managers/SFXManager.h"

MouseScript::MouseScript(sf::FloatRect area, MouseController* inputController, AnimationController* animController, Collider* collider, HitBehaviorScript* hitScript)
	: AComponent("MouseScript", EComponentTypes::Script), playableArea(area), inputController(inputController), animController(animController), collider(collider), hitScript(hitScript)
{
	this->collider->SetCollisionListener(this);

	isFlipped = false;

	mouseEatAudio = new sf::Sound();
	mouseEatAudio->setVolume(70.f);
	mouseEatAudio->setBuffer(*SFXManager::GetInstance()->GetAudio("Eat"));
}

MouseScript::~MouseScript() 
{

}

void MouseScript::Perform()
{
	MouseController::KeyDictionary keyInputs = inputController->GetHeldKeyInputs();
	HandleMovement(keyInputs);
	
	// check to flip sprite
	if (keyInputs[sf::Keyboard::A] && !isFlipped) isFlipped = true;
	else if (keyInputs[sf::Keyboard::D] && isFlipped) isFlipped = false;
	animController->FlipSprite(isFlipped);

	// update collider
	sf::FloatRect bounds = (owner->GetSprite() == NULL) ? sf::FloatRect(0, 0, 0, 0) : owner->GetSprite()->getGlobalBounds();
	collider->SetLocalBounds(bounds); 
}

void MouseScript::OnCollisionEnter(AGameObject* collidedObj)
{
	switch (collidedObj->Tag)
	{
	case EObjectTags::Cheese:
		animController->SetTrigger("isEating");
		mouseEatAudio->play();
		ScoreManager::GetInstance()->UpdateScore(1);
		break;
	case EObjectTags::Enemy:
		hitScript->OnHit();
		ScoreManager::GetInstance()->UpdateScore(-1);
		break;
	default:
		break;
	}
}

void MouseScript::OnCollisionExit(AGameObject* collidedObj)
{

}

void MouseScript::HandleMovement(MouseController::KeyDictionary& keyInputs)
{
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
	sf::Vector2f newPos = ApplyMovementRestrictions(movement); 
	owner->SetLocalPosition(newPos.x, newPos.y);
}

sf::Vector2f MouseScript::ApplyMovementRestrictions(sf::Vector2f movement)
{
	sf::Vector2f currentPos = owner->GetLocalPosition();

	if (owner->GetSprite() == NULL)
	{
		return currentPos;
	}

	sf::FloatRect spriteRect = owner->GetSprite()->getGlobalBounds();

	float rightLimit = playableArea.left + playableArea.width; 
	float rightDiff = rightLimit - (currentPos.x + spriteRect.width / 2 + movement.x);
	if (rightDiff < 0) 
	{
		movement.x += rightDiff; 
	}

	float leftLimit = playableArea.left; 
	float leftDiff = (currentPos.x - spriteRect.width / 2 + movement.x) - leftLimit; 
	if (leftDiff < 0) 
	{
		movement.x -= leftDiff;	 
	}

	float lowerLimit = playableArea.top + playableArea.height; 
	float lowerDiff = lowerLimit - (currentPos.y + spriteRect.height / 2 + movement.y);
	if (lowerDiff < 0) 
	{
		movement.y += lowerDiff;
	}

	float upperLimit = playableArea.top;
	float upperDiff = (currentPos.y - spriteRect.height / 2 + movement.y) - upperLimit;
	if (upperDiff < 0) 
	{
		movement.y -= upperDiff;
	}

	return currentPos + movement;  
}