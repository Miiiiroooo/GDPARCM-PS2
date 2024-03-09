#include "FinalScreen.h"
#include "../Components/Scripts/VideoHandler.h"
#include "../UI/BasicUIObject.h"
#include "../Game.h"

FinalScreen::FinalScreen() : AGameObject("FinalScreen")
{
	videoHandler = NULL;
}

FinalScreen::~FinalScreen()
{

}

void FinalScreen::Initialize()
{
	BasicUIObject* videoFrame = new BasicUIObject("VideoFrame");
	videoFrame->SetGlobalPosition(Game::WINDOW_WIDTH / 2, Game::WINDOW_HEIGHT / 2);
	this->AttachChild(videoFrame);

	videoHandler = new VideoHandler(videoFrame);
	this->AttachComponent(videoHandler);
}

VideoHandler* FinalScreen::GetVideoHandler()
{
	return videoHandler;
}