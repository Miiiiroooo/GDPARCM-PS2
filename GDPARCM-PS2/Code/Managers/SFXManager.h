#pragma once
#include <SFML/Graphics.hpp> 
#include <SFML/Audio.hpp>
#include <unordered_map>

class SFXManager : sf::NonCopyable
{
// methods
public:
	static SFXManager* GetInstance();

	sf::SoundBuffer* GetAudio(std::string);
	sf::SoundBuffer* GetStreamedAudio();
	void LoadAllLoadingScreenAudio(std::string directory);
	void LoadStreamedAudio(std::string directory);

private:
	SFXManager() {};
	void LoadAudio(std::string, std::string, bool isStreamedAsset);


// attributes
private:
	static SFXManager* sharedInstance;
	std::unordered_map<std::string, sf::SoundBuffer*> audioMap;
	sf::SoundBuffer* streamedAudio;
};