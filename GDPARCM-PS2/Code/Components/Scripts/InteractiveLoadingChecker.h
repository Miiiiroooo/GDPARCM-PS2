#pragma once
#include "../AComponent.h"

class InteractiveLoadingChecker : public AComponent
{
public:
	InteractiveLoadingChecker();
	~InteractiveLoadingChecker();

	void Perform() override;
};

