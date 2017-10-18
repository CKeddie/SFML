#pragma once
#include "SFML\Graphics.hpp"
class Tileset
{
public:
	Tileset(int, int, sf::Texture*);
	~Tileset();
	sf::Sprite* GetTile(int);
private:
	std::vector<sf::IntRect> _source_rects;
	sf::Sprite* _atlas;

};

