#pragma once

#include <map>
#include "SFML\Graphics\Texture.hpp"
#include "SFML\Graphics\Sprite.hpp"
#include "Map.h"

class AssetManager
{
public:
	AssetManager(const char*);
	~AssetManager();
	sf::Texture * LoadTexture(std::string);
	sf::Texture * GetTexture(std::string);
	sf::Sprite* TextureToSprite(std::string, int w = 0, int h = 0);
	sf::Font * LoadFont(std::string);
	sf::Font * GetFont(std::string);
private:
	std::string root;
	std::map<std::string, sf::Texture*> _sprites;
	std::map<std::string, Map*> _maps;
	std::map<std::string, sf::Font*> _fonts;
};

