#include "TextureManager.h"
#include <fstream>
#include <iostream>
#include <filesystem>
#include "../Game.h"
#include "../StringUtils.h"
#include "../MultiThreading/IETThread.h"


TextureManager* TextureManager::sharedInstance = NULL;

TextureManager* TextureManager::GetInstance()
{
	if (sharedInstance == NULL)
	{
		sharedInstance = new TextureManager();
	}

	return sharedInstance;
}

sf::Texture* TextureManager::GetTexture(std::string key)
{
	if (textureMap[key] != NULL)
	{
		return textureMap[key];
	}
	else
	{
		std::cout << "No texture found for " << key << std::endl; 
		return NULL;
	}
}

sf::Texture* TextureManager::GetStreamTexture(int index)
{
	if (index > streamTexturesList.size() - 1)
	{
		return NULL;
	}

	return streamTexturesList[index];
}

void TextureManager::LoadFromTextFile()
{
	std::ifstream stream("Media/assets.txt");
	
	// Load background texture
	std::string temp; 
	std::getline(stream, temp); 
	LoadTexture(GetAssetName(temp), temp, false); 

	// Get Icon Name
	std::getline(stream, this->baseIconName); 

	stream.close();
}

void TextureManager::LoadIcon(int iconID)
{
	IETThread::Sleep(500);

	std::string iconID_string = std::to_string(iconID);
	int digits = iconID_string.length();
	iconID_string.insert(0, 3 - digits, '0');
	std::string fullIconName = this->baseIconName + iconID_string + ".png"; 

	LoadTexture(GetAssetName(fullIconName), fullIconName, true);  
}

std::string TextureManager::GetAssetName(std::string filepath)
{
	std::vector<std::string> tokens = StringUtils::Split(filepath, '/'); // get tokens from directory
	return StringUtils::Split(tokens[tokens.size() - 1], '.')[0];  // remove ".png" from the string
}

void TextureManager::LoadTexture(std::string key, std::string path, bool isStreamAsset)
{
	sf::Texture* texture = new sf::Texture;

	if (texture->loadFromFile(path))
	{
		textureMap[key] = texture;

		if (isStreamAsset) 
		{
			streamTexturesList.push_back(texture);
		}

		//std::cout << Game::GetInstance()->GetCurrentGameTime() << " " << " Texture loaded: " << key << " " << textureMap.size() << "\n";
	}
	else
	{
		std::cout << "Texture not loaded: " << key << " " << path << "\n";
	}
}