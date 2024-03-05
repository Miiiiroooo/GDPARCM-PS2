#pragma once
#include <SFML/Graphics.hpp>
#include <unordered_map>

class FontManager : sf::NonCopyable
{
public:
	static FontManager* GetInstance();

	void LoadAll();
	sf::Font* GetFont(std::string);

private:
	FontManager() {};
	void LoadFont(std::string, std::string);


private:
	static FontManager* sharedInstance;
	std::unordered_map<std::string, sf::Font*> fontMap;
};