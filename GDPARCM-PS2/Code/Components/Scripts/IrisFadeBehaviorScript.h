#pragma once
#include "../AComponent.h"
#include "../../Enums/EIrisStates.h"

class IrisFadeBehaviorScript : public AComponent
{
public:
	IrisFadeBehaviorScript(float mouseX);
	~IrisFadeBehaviorScript();
	
	void Initialize();
	void OnFadeOut();
	void Perform() override;

private:
	void DisplayIrisTexture();
	void OnFirstHalf();
	void OnStopped();
	void OnSecondHalf();


private:
	sf::RectangleShape irisBackground;
	sf::CircleShape irisCircle;
	sf::RenderTexture renderTexture;
	bool hasRenderTextureFailed;
	float mouseX;

	const float FADE_OUT_DURATION = 4.8f;
	const float STOP_DURATION = 1.2f;
	const float STOP_TIME_FRAME = FADE_OUT_DURATION - 0.6f;
	EIrisStates currentState;

	float elapsedFadeOutTime;
	float elapsedStopTime;
	sf::Vector2f currentScale;
	sf::Vector2f decreaseScaleSpeed;
};