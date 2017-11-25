#include "CollisionLayer.h"
#include "Entity.h"
#include "PhysicsBody.h"


CollisionLayer::CollisionLayer(int w, int h, int tw, int th)
	: IntLayer::IntLayer(w, h)
{
	_tile_width = tw;
	_tile_height = th;
}

CollisionLayer::~CollisionLayer()
{
	IntLayer::~IntLayer();
}

void CollisionLayer::Update(float deltaTime)
{
	Broadphase();
}

float CollisionLayer::IntervalDistance(float minA, float maxA, float minB, float maxB)
{
	if (minA < minB)
	{
		return minB - maxA;
	}
	else {
		return minA - maxB;
	}
}

void CollisionLayer::Draw(sf::RenderWindow * window, Tileset * tileset)
{
	for (unsigned int y = 0; y < _height; ++y)
	{
		for (unsigned int x = 0; x < _width; ++x)
		{
			int idx = x + y * _width;
			int tidx = _indices[idx];
			if (tidx > 0)
			{
				sf::Sprite* sprite = tileset->GetTile(tidx);

				int w = sprite->getTextureRect().width;
				int h = sprite->getTextureRect().height;

				sprite->setPosition(
					sf::Vector2f((float)x * (float)w - (float)w / 2.0f, (float)y * (float)w - (float)w / 2.0f));
				window->draw(*sprite);
			}
		}
	}
	window->draw(_vertices);
}

void CollisionLayer::AddEntities(Entity * entity)
{
	_entities.push_back(entity);
}

//never again.
void CollisionLayer::Broadphase()
{
	bool is_grounded = false;
	bool is_walled = false;
	
	//loop through each entity
	for (unsigned int i = 0; i < _entities.size(); i++)
	{
		BoxCollider * entity_bounds = _entities[i]->GetComponent<BoxCollider>();
		PhysicsBody * entity_body = _entities[i]->GetComponent<PhysicsBody>();
		sf::Vector2f entity_position = _entities[i]->Position() + entity_bounds->RectGetOffset();
	
		//float velocity_projection = entity_body.GetVelocity().x * 

		//project collider to x and y axis respectively
		float x_min_a = entity_bounds->GetMin(sf::Vector2f(1, 0));
		float x_max_a = entity_bounds->GetMax(sf::Vector2f(1, 0));
		float y_min_a = entity_bounds->GetMin(sf::Vector2f(0, 1));
		float y_max_a = entity_bounds->GetMax(sf::Vector2f(0, 1));

		//add velocity
		int map_index_x = int(entity_position.x  / _tile_width );
		int map_index_y = int(entity_position.y  / _tile_height);
											 				
		sf::Vector2f overlap;

		//iterate grid of 9 around map index of player
		for (int y = 0; y <= 1; y++)
		{
			for (int x = -1; x <= 1; x++)
			{
				//check valid tile
				if (this->GetIndex(map_index_x + x,  map_index_y + y))
				{
					//set position and size of the map tile
					sf::Vector2f tile_coord = sf::Vector2f(
							float((map_index_x + x) * _tile_width), 
							float((map_index_y + y) * _tile_height));

					sf::Vector2f tile_size = sf::Vector2f(
						float(_tile_width / 2), 
						float(_tile_height / 2));

					//set min and max points of the tile
					float x_min_b = tile_coord.x - tile_size.x;
					float x_max_b = tile_coord.x + tile_size.x;
					float y_min_b = tile_coord.y - tile_size.y;
					float y_max_b = tile_coord.y + tile_size.y;

					//check the overlap of each axis
					float y_overlap = std::roundf(IntervalDistance(y_min_a, y_max_a, y_min_b, y_max_b));
					float x_overlap = std::roundf(IntervalDistance(x_min_a, x_max_a, x_min_b, x_max_b));
             
					bool is_colliding = x_overlap <= 0 && y_overlap <= 0;
					
					//Collision found
					if (is_colliding)
					{						
						sf::Vector2f d = tile_coord - entity_position;
						if (std::abs(x_overlap) < std::abs(y_overlap))
						{
							if (d.x < 0)
								x_overlap = -x_overlap + 1;
							else
								x_overlap = x_overlap - 1;
							overlap.x = x_overlap;

							is_walled |= true;

						}
						else
						{
							if (d.y < 0)
							{
								y_overlap = -y_overlap;
								entity_body->SetTargetSpeedY(10.0f);
							}
							else
								is_grounded |= true;

							overlap.y = y_overlap;
						}
					}
				}//end check valid tile
			}//end x
		}//end y	
		entity_body->SetGrounded(is_grounded);
		entity_body->SetWalled(is_walled);
		_entities[i]->Translate(overlap);
	}//end i
}