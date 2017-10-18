#include "Map.h"

Map::Map(int w, int h, int tw, int th)
{
	_size_x = w;
	_size_y = h;
	_grid_width = tw;
	_grid_height = th;
}


void Map::AddLayer(MapLayer * layer)
{
	_map_layers.push_back(layer);
}


void Map::LoadLayer(std::string filename)
{
	MapLayer* layer = new MapLayer(_size_x, _size_y); 
	layer->LoadLayer(filename);
	_map_layers.push_back(layer);
}

void Map::LoadDebugTileset(Tileset* tileset)
{
	_debug_tileset = tileset;
}

void Map::LoadCollisionMap(std::string file)
{
	CollisionLayer* layer = new CollisionLayer(_size_x, _size_y, 32, 32);
	layer->LoadLayer(file);
	_collision_layer = layer;
}

CollisionLayer * Map::GetCollisionLayer()
{
	return _collision_layer;
}

sf::Vector2i Map::GetSize()
{
	return sf::Vector2i(_size_x, _size_y);
}


void Map::Draw(sf::RenderWindow * window)
{
	for (int i = 0; i < (int)_map_layers.size(); ++i)
		_map_layers[i]->Draw(window, _tileset);

	if(_debug_tileset && _collision_layer)
		_collision_layer->Draw(window, _debug_tileset);
}

void Map::SetTileset(Tileset * tileset)
{
	_tileset = tileset;
}

Map::~Map()
{
	delete _tileset;
	_tileset = nullptr;

	for (int i = 0; i < (int)_map_layers.size(); ++i)
	{
		delete _map_layers[i];
		_map_layers[i] = nullptr;
	}

	delete _debug_tileset;
	_debug_tileset = nullptr;

	delete _collision_layer;
	_collision_layer = nullptr;

	_map_layers.shrink_to_fit();
}

void Map::Update(float dt)
{
	_collision_layer->Update(dt);
}
