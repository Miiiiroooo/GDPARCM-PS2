#include "SFXManager.h"
#include <fstream>
#include <iostream>

// static declarations of the SFXManager Class
SFXManager* SFXManager::sharedInstance = NULL;

SFXManager* SFXManager::GetInstance()
{
	if (sharedInstance == NULL)
		sharedInstance = new SFXManager;

	return sharedInstance;
}


void SFXManager::LoadAll(std::string directory)
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
			LoadAudio(key, path);
		}
	}

	inFile.close();
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

void SFXManager::LoadAudio(std::string key, std::string path)
{
	sf::SoundBuffer* soundBuffer = new sf::SoundBuffer;

	soundBuffer->loadFromFile(path);
	audioMap[key] = soundBuffer;
}