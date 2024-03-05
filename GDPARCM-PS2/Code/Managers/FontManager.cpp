#include "FontManager.h"
#include <iostream>


FontManager* FontManager::sharedInstance = NULL;

FontManager* FontManager::GetInstance()
{
	if (sharedInstance == NULL)
		sharedInstance = new FontManager();

	return sharedInstance;
}

void FontManager::LoadAll()
{
	LoadFont("default", "Media/Fonts/Sansation.ttf");
}

sf::Font* FontManager::GetFont(std::string key)
{
	if (fontMap[key] != NULL)
	{
		return fontMap[key];
	}
	else
	{
		std::cout << "No font found for: " << key;
		return NULL;
	}
}

void FontManager::LoadFont(std::string key, std::string path)
{
	sf::Font* font = new sf::Font();
	font->loadFromFile(path);
	fontMap[key] = font;
}