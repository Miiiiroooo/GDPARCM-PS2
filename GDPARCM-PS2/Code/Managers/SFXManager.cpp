#include "SFXManager.h"
#include <fstream>
#include <iostream>
#include "../StringUtils.h"

// static declarations of the SFXManager Class
SFXManager* SFXManager::sharedInstance = NULL;

SFXManager* SFXManager::GetInstance()
{
	if (sharedInstance == NULL)
		sharedInstance = new SFXManager;

	return sharedInstance;
}

sf::SoundBuffer* SFXManager::GetAudio(std::string key)
{
	if (audioMap[key] != NULL)
	{
		return audioMap[key];
	}
	else
	{
		std::cout << "No audio found for " << key << std::endl;
		return NULL;
	}
}

sf::SoundBuffer* SFXManager::GetStreamedAudio()
{
	return streamedAudio;
}

void SFXManager::LoadAllLoadingScreenAudio(std::string directory)
{
	std::string key, path;
	std::ifstream inFile;

	inFile.open(directory);

	if (!inFile)
	{
		std::cerr << "Unable to open the LoadAudio.txt\n\nClosing Window..." << std::endl;
	}
	else
	{
		while (inFile >> key >> path)
		{
			LoadAudio(key, path, false);
		}
	}

	inFile.close();
}

void SFXManager::LoadStreamedAudio(std::string directory)
{
	std::vector<std::string> tokens = StringUtils::Split(directory, '/'); // get tokens from directory
	std::string key = StringUtils::Split(tokens[tokens.size() - 1], '.')[0];  // remove ".png" from the string

	LoadAudio(key, directory, true);
}

void SFXManager::LoadAudio(std::string key, std::string path, bool isStreamedAsset)
{
	sf::SoundBuffer* soundBuffer = new sf::SoundBuffer;

	if (soundBuffer->loadFromFile(path))
	{
		audioMap[key] = soundBuffer;

		if (isStreamedAsset)
		{
			streamedAudio = soundBuffer;
		}
	}
	else
	{
		std::cout << "Audio not loaded: " << key << " " << path << "\n";
	}
}