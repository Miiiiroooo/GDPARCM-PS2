#include "CatScript.h"
#include "../../Managers/SFXManager.h"

CatScript::CatScript(sf::FloatRect area, AnimationController* animController, Collider* collider) 
	: AComponent("CatScript", EComponentTypes::Script), playableArea(area), animController(animController), collider(collider), mouse(NULL)
{
	isFlipped = false;

	currentDelayTime = GetRandomDelay();
	elapsedTime = 0.f;
	isOnSceneTransition = false;
	currentState = ECatStates::Delayed; 
	travelSpeed = sf::Vector2f(0.f, 0.f);

	catMeowAudio = new sf::Sound();
	catMeowAudio->setVolume(70.f);
	catMeowAudio->setBuffer(*SFXManager::GetInstance()->GetAudio("CatMeow"));
}

CatScript::~CatScript()
{
	delete catMeowAudio;
}

void CatScript::SetMouse(AGameObject* mouse)
{
	this->mouse = mouse;
}

void CatScript::OnSceneTransition()
{
	isOnSceneTransition = true;
	currentState = ECatStates::Delayed;
}

//void CatScript::OnSceneTransitionPounce()
//{
//	elapsedTime = 0;
//	currentState = ECatStates::Ready; 
//	animController->SetTrigger("isPouncing"); 
//}

void CatScript::Perform()
{
	switch (currentState)
	{
		case ECatStates::Delayed:
			OnDelay();
			break;
		case ECatStates::Ready:
			OnReady();
			break;
		case ECatStates::Pouncing:
			OnPounce();
			break;
		default:
			break;
	}
}

float CatScript::GetRandomDelay()
{
	return MIN_DELAY + (float)rand() * (MAX_DELAY - MIN_DELAY) / RAND_MAX;
}

void CatScript::OnDelay()
{
	if (isOnSceneTransition)
	{
		return;
	}

	elapsedTime += deltaTime.asSeconds(); 

	if (currentDelayTime < 0) 
	{
		currentDelayTime = GetRandomDelay(); 
	}

	if (elapsedTime > currentDelayTime) 
	{
		elapsedTime = 0; 
		currentDelayTime = -1.f; 
		currentState = ECatStates::Ready; 
		animController->SetTrigger("isPouncing");
	}
}

void CatScript::OnReady()
{
	elapsedTime += deltaTime.asSeconds();

	if (elapsedTime > TIME_FRAME_TO_POUNCE)
	{
		elapsedTime = 0;
		currentState = ECatStates::Pouncing;
		catMeowAudio->play();

		sf::Vector2f mousePos = mouse->GetGlobalPosition();
		sf::Vector2f catPos = owner->GetGlobalPosition(); 
		sf::Vector2f direction = isOnSceneTransition ? (catPos - mousePos) * 30.f : (mousePos - catPos) * 1.75f;

		float xSpeed = direction.x / POUNCE_TRAVEL_TIME; 
		float ySpeed = direction.y / POUNCE_TRAVEL_TIME; 

		travelSpeed = sf::Vector2f(xSpeed, ySpeed); 
		travelSpeed *= deltaTime.asSeconds(); 
	}
}

void CatScript::OnPounce()
{
	elapsedTime += deltaTime.asSeconds();

	if (elapsedTime > POUNCE_TRAVEL_TIME)
	{ 
		elapsedTime = 0;
		currentState = ECatStates::Delayed; 
	}

	// movement
	HandleMovement();

	// check to flip sprite
	if (travelSpeed.x < 0 && !isFlipped) isFlipped = true; 
	else if (travelSpeed.x > 0 && isFlipped) isFlipped = false; 
	animController->FlipSprite(isFlipped); 

	// update collider
	sf::FloatRect bounds = (owner->GetSprite() == NULL) ? sf::FloatRect(0, 0, 0, 0) : owner->GetSprite()->getGlobalBounds(); 
	collider->SetLocalBounds(bounds); 
}

void CatScript::HandleMovement()
{
	if (owner->GetSprite() == NULL)
	{
		return;
	}

	sf::Vector2f catPos = owner->GetGlobalPosition(); 

	if (!isOnSceneTransition) 
	{
		sf::FloatRect spriteRect = owner->GetSprite()->getGlobalBounds(); 

		float rightLimit = playableArea.left + playableArea.width; 
		float rightDiff = rightLimit - (catPos.x + spriteRect.width / 2 + travelSpeed.x); 
		if (rightDiff < 0) 
		{
			//travelSpeed.x += rightDiff;
			travelSpeed.x *= -1; 
		}

		float leftLimit = playableArea.left; 
		float leftDiff = (catPos.x - spriteRect.width / 2 + travelSpeed.x) - leftLimit; 
		if (leftDiff < 0)
		{
			//travelSpeed.x -= leftDiff;
			travelSpeed.x *= -1; 
		}

		float lowerLimit = playableArea.top + playableArea.height; 
		float lowerDiff = lowerLimit - (catPos.y + spriteRect.height / 2 + travelSpeed.y); 
		if (lowerDiff < 0) 
		{
			//travelSpeed.y += lowerDiff;
			travelSpeed.y *= -1; 
		}

		float upperLimit = playableArea.top; 
		float upperDiff = (catPos.y - spriteRect.height / 2 + travelSpeed.y) - upperLimit; 
		if (upperDiff < 0) 
		{
			//travelSpeed.y -= upperDiff;
			travelSpeed.y *= -1; 
		}
	}

	sf::Vector2f newPos = catPos + travelSpeed; 
	owner->SetGlobalPosition(newPos.x, newPos.y);
}