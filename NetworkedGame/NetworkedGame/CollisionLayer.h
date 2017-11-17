#pragma once

#include "ILayer.h"
#include "SFML\Graphics.hpp"
#include "Tileset.h"
#include "BoxCollider.h"

class CollisionLayer 
	: public IntLayer
{
public:
	CollisionLayer(int, int, int, int);
	~CollisionLayer();
	void Update(float);
	float IntervalDistance(float minA, float maxA, float minB, float maxB);
	void Draw(sf::RenderWindow*, Tileset* tileset);
	void AddEntities(Entity* entity);
	void CheckValidTile();
protected:
	int _tile_width, _tile_height;	
	std::vector<Entity*> _entities;
	void Broadphase();
	void Narrowphase();
	sf::VertexArray _vertices;
};

