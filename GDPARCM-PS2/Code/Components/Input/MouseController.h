#pragma once
#include "GenericInputController.h"
#include <unordered_map>

class MouseController : public GenericInputController
{
public:
	typedef std::unordered_map<sf::Keyboard::Key, bool> KeyDictionary; 

public:
	MouseController();
	~MouseController();

	void Perform() override;

	KeyDictionary& GetHeldKeyInputs();


private:
	KeyDictionary heldKeyInputs;
};

