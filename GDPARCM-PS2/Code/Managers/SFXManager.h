#pragma once
#include <SFML/Graphics.hpp> 
#include <SFML/Audio.hpp>
#include <unordered_map>

class SFXManager : sf::NonCopyable
{
// methods
public:
	static SFXManager* GetInstance();
	void LoadAll(std::string directory);
	sf::SoundBuffer* GetAudio(std::string);

private:
	SFXManager() {};

	void LoadAudio(std::string, std::string);


// attributes
private:
	std::unordered_map<std::string, sf::SoundBuffer*> audioMap;
	static SFXManager* sharedInstance;
};