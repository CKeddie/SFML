#include "MapLayer.h"

#include <iostream>


MapLayer::MapLayer(int w, int h) 
	: IntLayer::IntLayer(w, h)
{	

}

MapLayer::~MapLayer()
{
	IntLayer::~IntLayer();
}

void MapLayer::Draw(sf::RenderWindow * window, Tileset* tileset)
{
	for (int y = 0; y < _height; ++y)
	{
		for (int x = 0; x < _width; ++x)
		{
			int idx = x + y * _width;
			int tidx = _indices[idx];
			if (tidx != -1 && tidx != 0)
			{
				sf::Sprite* sprite = tileset->GetTile(tidx); 
				int w = sprite->getTextureRect().width;
				int h = sprite->getTextureRect().height;
				sprite->setPosition(sf::Vector2f(float(x *  w - w/2), float(y * h - h/2)));
				window->draw(*sprite);
			}
		}
	}
}