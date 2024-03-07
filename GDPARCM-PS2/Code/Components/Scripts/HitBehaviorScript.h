#pragma once
#include "../AComponent.h"
#include "../Renderer.h"
#include "../../Physics/Collider.h"

class HitBehaviorScript : public AComponent
{
public:
	HitBehaviorScript(std::string name, Renderer* renderer, Collider* collider);
	~HitBehaviorScript();

	void OnHit();
	void Perform() override;


private:
	Renderer* renderer;
	Collider* collider;

	const float INVINCIBILITY_DURATION = 2.75f;
	const float BLINK_IN_DURATION = 0.2f;
	const float BLINK_OUT_DURATION = 0.12f;
	
	bool isHit;
	float elapsedTime;
	float elapsedBlinkTime;
	bool isBlinkingIn;
};