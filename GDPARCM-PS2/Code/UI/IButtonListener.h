#pragma once

class UIButton;   // forward declaration to avoid circular dependency

class IButtonListener
{
public:
	virtual ~IButtonListener() {}

	virtual void OnButtonClick(UIButton* button) = 0;
	virtual void OnButtonReleased(UIButton* button) = 0;


protected:
	IButtonListener() {}
};