#pragma once
#include <SFML/Audio.hpp>
#include "../AComponent.h"
#include "../../Scenes/IFinishedSceneTransitionListener.h"

class VideoHandler : public AComponent, public IFinishedSceneTransitionListener
{
public:
	VideoHandler(AGameObject* videoFrame);
	~VideoHandler();

	void Perform() override;
	void OnFinishedSceneTransition() override;

	void AddSortedTexturesToList(std::vector<sf::Texture*>& texturesList);

private:
	void UpdateVideoFrame();


private:
	const int VIDEO_FPS = 30 / 2;
	const float SECONDS_PER_FRAME = 1.f / (float)VIDEO_FPS;
	float elapsedTime;
	int currentIndex;

	const float TEXTURE_SCALE = 3.f;
	std::vector<sf::Texture*> texturesList;
	AGameObject* videoFrame;

	const std::string AUDIO_KEY = "TomAndJerry";
	sf::Sound* tomAndJerryAudio;
};

