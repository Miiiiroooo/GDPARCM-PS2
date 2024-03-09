#include "VideoHandler.h"
#include "../../GameObjects/AGameObject.h"
#include "../../Managers/SFXManager.h"
#include "../../Managers/TextureManager.h"
#include "../../Managers/ApplicationManager.h"

VideoHandler::VideoHandler(AGameObject* videoFrame) : AComponent("VideoHandler", EComponentTypes::Script), videoFrame(videoFrame)
{
	elapsedTime = 0;
	currentIndex = 0;
	this->tomAndJerryAudio = NULL;
}

VideoHandler::~VideoHandler()
{
	videoFrame = NULL;
}

void VideoHandler::Perform()
{
	elapsedTime += deltaTime.asSeconds();

	if (currentIndex >= texturesList.size())
	{
		ApplicationManager::GetInstance()->ApplicationQuit();
		return;
	}

	if (elapsedTime > SECONDS_PER_FRAME)
	{
		elapsedTime = 0;
		UpdateVideoFrame();
		currentIndex++;
	}
}

void VideoHandler::OnFinishedSceneTransition()
{
	currentIndex = 0;

	tomAndJerryAudio = new sf::Sound();
	tomAndJerryAudio->setBuffer(*SFXManager::GetInstance()->GetAudio(AUDIO_KEY));
	tomAndJerryAudio->play();
}

void VideoHandler::AddSortedTexturesToList(std::vector<sf::Texture*>& texturesList)
{
	this->texturesList.insert(this->texturesList.end(), texturesList.begin(), texturesList.end());
}

void VideoHandler::UpdateVideoFrame()
{
	sf::Sprite* sprite = videoFrame->GetSprite();  
	sprite->setTexture(*texturesList[currentIndex]);  
	sf::Vector2u textureSize = sprite->getTexture()->getSize();  
	sprite->setOrigin(textureSize.x / 2, textureSize.y / 2);  
	sprite->setScale(TEXTURE_SCALE, TEXTURE_SCALE); 
}