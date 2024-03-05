#pragma once
#include "GenericInputController.h"
#include "../../UI/IButtonListener.h"

class UIButtonInputController : public GenericInputController
{
public:
	UIButtonInputController(std::string name, IButtonListener* listener);
	~UIButtonInputController();

	void Perform() override;


private:
	IButtonListener* buttonListener;
	bool pressed = false;
};