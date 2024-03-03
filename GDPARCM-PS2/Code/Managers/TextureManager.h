#pragma once
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include "EStreamingTypes.h"

class TextureManager : sf::NonCopyable
{
public:
	static TextureManager* GetInstance();
	
	sf::Texture* GetTexture(std::string key);
	sf::Texture* GetStreamTexture(int index);
	void LoadAllMainAssets();

	void LoadFromTextFile();
	void LoadIcon(int iconID);

private:
	TextureManager() {};
	std::string GetAssetName(std::string filepath);
	void LoadTexture(std::string key, std::string path, bool isStreamAsset);


private:
	static TextureManager* sharedInstance;
	const std::string STREAMING_PATH = "Media/Streaming/";

	std::string baseIconName;
	std::unordered_map<std::string, sf::Texture*> textureMap;
	std::vector<sf::Texture*> streamTexturesList;
};

