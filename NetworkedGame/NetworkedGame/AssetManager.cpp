#include "AssetManager.h"
#include <iostream>

AssetManager::AssetManager(const char * directory)
{
	root = directory;
}

AssetManager::~AssetManager()
{
	_sprites.clear();
}

sf::Texture* AssetManager::LoadTexture(std::string name, std::string directory)
{
	sf::Texture* txr = new sf::Texture();
	if (!txr->loadFromFile(directory + "/" + name))
	{
		delete txr;
		txr = nullptr;
		std::cout << "\nCould not locate file: " << name << std::endl;
		return NULL;
	}
	
	std::string delimiter = ".";
	
	std::string id = name.substr(0, name.find(delimiter));

	_sprites[id] = txr;		
	
	return _sprites[id];
}

sf::Texture* AssetManager::GetTexture(std::string id)
{
	return _sprites[id];
}

void AssetManager::LoadMap(std::string, std::string)
{
	
}

sf::Sprite * AssetManager::TextureToSprite(std::string str, int w, int h)
{
	return new sf::Sprite(*_sprites[str], sf::IntRect(0, 0, w, h));
}
