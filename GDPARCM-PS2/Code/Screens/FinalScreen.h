#pragma once
#include "../GameObjects/AGameObject.h"
#include "../Components/Scripts/VideoHandler.h"

class FinalScreen : public AGameObject
{
public:
	FinalScreen();
	~FinalScreen();

	void Initialize() override;
	VideoHandler* GetVideoHandler();


private:
	VideoHandler* videoHandler;
};