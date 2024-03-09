#include "IrisFadeBehaviorScript.h"
#include "../../GameObjects/LoadingScreen/IrisFadeObject.h"
#include "../../GameObjects/AGameObject.h"
#include "../../Game.h"
#include <iostream>


IrisFadeBehaviorScript::IrisFadeBehaviorScript(float mouseX) : AComponent("IrisFadeBehaviorScript", EComponentTypes::Script), mouseX(mouseX)
{
	currentState = EIrisStates::Unknown;
	elapsedFadeOutTime = 0;
	elapsedStopTime = 0;
	hasRenderTextureFailed = false;
}

IrisFadeBehaviorScript::~IrisFadeBehaviorScript()
{

}

void IrisFadeBehaviorScript::Initialize()
{
	float width = Game::WINDOW_WIDTH * 2.5;
	float height = Game::WINDOW_HEIGHT * 2.5;
	float radius = (Game::WINDOW_WIDTH / 2) + std::abs(Game::WINDOW_WIDTH / 2 - mouseX) + 100;

	irisBackground = sf::RectangleShape(sf::Vector2f(width, height));
	irisBackground.setOrigin(width / 2, height / 2);
	irisBackground.setPosition(width / 2, height / 2); 
	irisBackground.setFillColor(sf::Color::Black); 
	irisBackground.setOutlineThickness(0); 

	irisCircle = sf::CircleShape(radius);
	irisCircle.setOrigin(radius, radius); 
	irisCircle.setPosition(width / 2, height / 2); 
	irisCircle.setFillColor(sf::Color::Magenta);
	irisCircle.setOutlineThickness(0); 

	if (!renderTexture.create(width, height))
	{
		std::cerr << "Failed to create iris texture\n";
		hasRenderTextureFailed = true;
		return;
	}

	sf::Sprite* ownerSprite = owner->GetSprite();

	if (ownerSprite == NULL) 
	{
		ownerSprite = new sf::Sprite(); 
		owner->UpdateSprite(ownerSprite);
	}

	ownerSprite->setOrigin(width / 2, height / 2);

	currentScale = irisCircle.getScale(); 
	decreaseScaleSpeed = sf::Vector2f(currentScale.x, currentScale.y) / FADE_OUT_DURATION; 
}

void IrisFadeBehaviorScript::DisplayIrisTexture()
{
	renderTexture.clear();
	renderTexture.draw(irisBackground); 
	renderTexture.display(); 

	sf::BlendMode bm;  
	bm.alphaSrcFactor = sf::BlendMode::Zero;  
	bm.colorDstFactor = sf::BlendMode::One;  

	renderTexture.draw(irisCircle, bm);  
	renderTexture.display(); 
	 
	sf::Sprite* ownerSprite = owner->GetSprite(); 
	ownerSprite->setTexture(renderTexture.getTexture()); 
}

void IrisFadeBehaviorScript::OnFadeOut()
{
	currentState = EIrisStates::First_Half;
}

void IrisFadeBehaviorScript::Perform()
{
	if (currentState == EIrisStates::Unknown || hasRenderTextureFailed)
	{
		return;
	}

	switch (currentState)
	{
		case EIrisStates::First_Half:
			OnFirstHalf();
			break;
		case EIrisStates::Stopped: 
			OnStopped();
			break;
		case EIrisStates::Second_Half:
			OnSecondHalf();
			break;
		default:
			break;
	}
}

void IrisFadeBehaviorScript::OnFirstHalf()
{
	elapsedFadeOutTime += deltaTime.asSeconds(); 

	if (elapsedFadeOutTime > STOP_TIME_FRAME) 
	{
		currentState = EIrisStates::Stopped; 
		return;
	}

	currentScale -= decreaseScaleSpeed * deltaTime.asSeconds(); 
	irisCircle.setScale(currentScale); 
	DisplayIrisTexture(); 
}

void IrisFadeBehaviorScript::OnStopped()
{
	elapsedStopTime += deltaTime.asSeconds(); 

	if (elapsedStopTime > STOP_DURATION) 
	{
		elapsedFadeOutTime = STOP_TIME_FRAME; 
		currentState = EIrisStates::Second_Half; 
	}
}

void IrisFadeBehaviorScript::OnSecondHalf()
{
	elapsedFadeOutTime += deltaTime.asSeconds(); 

	if (elapsedFadeOutTime > FADE_OUT_DURATION) 
	{
		IrisFadeObject* obj = (IrisFadeObject*)owner;
		if (!obj->IsFinishedTransitioning())
		{
			obj->OnFinishedTransition();
		}

		return;
	}

	currentScale -= decreaseScaleSpeed * deltaTime.asSeconds(); 
	irisCircle.setScale(currentScale); 
	DisplayIrisTexture(); 
}