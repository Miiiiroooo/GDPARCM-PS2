#include "TextureManager.h"
#include <fstream>
#include <iostream>
#include <filesystem>
#include <rapidjson/document.h>
#include <rapidjson/filereadstream.h>
#include <cassert>

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

void TextureManager::LoadAllLoadingScreenAssets()
{
	FILE* inFile = fopen("Media/SpriteSheetData.json", "rb");
	assert(inFile != NULL);

	char readBuffer[4096];
	rapidjson::FileReadStream jsonFile(inFile, readBuffer, sizeof(readBuffer));
	rapidjson::Document doc;

	doc.ParseStream(jsonFile);
	fclose(inFile);


	// initialize new sprites by obtaining the values of the parsed data
	for (rapidjson::Value::ConstMemberIterator data_itr = doc["data"].MemberBegin(); data_itr != doc["data"].MemberEnd(); ++data_itr)
	{
		std::string sourceFileName = data_itr->name.GetString(); 

		for (rapidjson::Value::ConstMemberIterator src_itr = data_itr->value.MemberBegin(); src_itr != data_itr->value.MemberEnd(); ++src_itr)
		{
			// init rect for each sprite in sprite sheet
			int x = src_itr->value["x"].GetInt();
			int y = src_itr->value["y"].GetInt(); 
			int width = src_itr->value["w"].GetInt();
			int height = src_itr->value["h"].GetInt(); 
			sf::Rect<int> rect(x, y, width, height); 

			// init texture from file with specified rect
			std::string dir = "Media/SpriteSheets/" + sourceFileName; 
			sf::Texture* texture = new sf::Texture(); 
			texture->loadFromFile(dir, rect);  // takes more time to load up 
			textureMap[src_itr->name.GetString()] = texture; 
		}
	}

	LoadTexture("Cheese", "Media/Sprites/Cheese.png", false);
}

void TextureManager::LoadStreamedAssets(std::string key)
{
	std::string path = STREAMING_PATH + key + ".png";
	LoadTexture(key, path, true);
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