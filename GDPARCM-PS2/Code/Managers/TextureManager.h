#pragma once
#include <SFML/Graphics.hpp>
#include <unordered_map>

class TextureManager : sf::NonCopyable
{
public:
	static TextureManager* GetInstance();
	
	sf::Texture* GetTexture(std::string key);
	sf::Texture* GetStreamTexture(int index);
	void LoadAllLoadingScreenAssets();
	void LoadStreamedAssets(std::string key);

private:
	TextureManager() {};
	void LoadTexture(std::string key, std::string path, bool isStreamAsset);


private:
	static TextureManager* sharedInstance;
	const std::string STREAMING_PATH = "Media/StreamedAssets/";

	std::unordered_map<std::string, sf::Texture*> textureMap;
	std::vector<sf::Texture*> streamTexturesList;
};

