#include "Tileset.h"



Tileset::Tileset(int tw, int th, sf::Texture * txr)
{
	_atlas = new sf::Sprite(*txr);
	
	int size_x = txr->getSize().x / tw;
	int size_y = txr->getSize().y / th;

	for (int y = 0; y < size_y; y++)
		for (int x = 0; x < size_x; x++)
			_source_rects.push_back(sf::IntRect(x * tw, y * th, tw, th));

	_atlas->setTextureRect(_source_rects[0]);
}



Tileset::~Tileset()
{
	delete _atlas;
	_atlas = nullptr;

	_source_rects.clear();
	_source_rects.~vector();
}

sf::Sprite * Tileset::GetTile(int index)
{
	_atlas->setTextureRect(_source_rects[index]);
	return _atlas;
}

