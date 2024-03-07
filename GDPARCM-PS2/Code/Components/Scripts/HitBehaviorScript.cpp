#include "HitBehaviorScript.h"
#include "../../Physics/PhysicsManager.h"

HitBehaviorScript::HitBehaviorScript(std::string name, Renderer* renderer, Collider* collider) : AComponent(name, EComponentTypes::Script), renderer(renderer), collider(collider)
{
	isHit = false;
	elapsedTime = 0.f;
	elapsedBlinkTime = 0.f;
	isBlinkingIn = false;
}

HitBehaviorScript::~HitBehaviorScript()
{

}

void HitBehaviorScript::OnHit()
{
	isHit = true;
	PhysicsManager::GetInstance()->UntrackObject(collider);

}

void HitBehaviorScript::Perform()
{
	if (!isHit) return;

	elapsedTime += deltaTime.asSeconds();
	elapsedBlinkTime += deltaTime.asSeconds();

	if (elapsedTime > INVINCIBILITY_DURATION)
	{
		elapsedTime = 0.f;
		elapsedBlinkTime = 0.f;
		isBlinkingIn = false;
		isHit = false;

		renderer->Enabled = true;
		PhysicsManager::GetInstance()->TrackObject(collider);
		return;
	}

	if (isBlinkingIn) // if should appear on screen
	{
		if (elapsedBlinkTime > BLINK_IN_DURATION)
		{
			elapsedBlinkTime = 0.f;
			isBlinkingIn = false;
		}
		else if (!renderer->Enabled)
		{
			renderer->Enabled = true;
		}
	}
	else if (!isBlinkingIn) // if should not appear on screen
	{
		if (elapsedBlinkTime > BLINK_OUT_DURATION)
		{
			elapsedBlinkTime = 0.f;
			isBlinkingIn = true;
		}
		else if (renderer->Enabled)
		{
			renderer->Enabled = false;
		}
	}
}