#pragma once

#include "MapLayer.h"
#include "CollisionLayer.h"

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

class Map
{
public:
	Map(int w, int h, int tw, int th);
	~Map();
	void Update(float);
	void Draw(sf::RenderWindow* window);
	void AddLayer(MapLayer* layer);
	void SetTileset(Tileset*);
	void LoadLayer(std::string file);
	void LoadDebugTileset(Tileset * tileset);
	void LoadCollisionMap(std::string file);
	CollisionLayer* GetCollisionLayer();
	sf::Vector2i GetSize();
private:
	int _size_x, _size_y;
	int _grid_width, _grid_height;
	Tileset* _tileset;
	Tileset* _debug_tileset;
	std::vector<MapLayer*> _map_layers;
	CollisionLayer* _collision_layer;
};

