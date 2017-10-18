#pragma once

#include "ILayer.h"
#include "SFML\Graphics.hpp"
#include "Tileset.h"

class MapLayer 
	: public IntLayer
{
public:
	MapLayer(int w, int h);
	~MapLayer();
	void Draw(sf::RenderWindow*, Tileset*);
};