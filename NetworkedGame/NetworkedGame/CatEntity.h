#pragma once

#include "Entity.h"
#include "SpriteRenderer.h"
#include "BoxCollider.h"
#include "PhysicsBody.h"

class CatEntity 
	: public Entity
{
public:
	enum Direction
	{
		Left = -1,
		Right = 1
	};
	CatEntity(sf::Vector2f, sf::Vector2f, float, sf::Vector2f, sf::Vector2f);
	CatEntity(float px, float py, float sx, float sy, float rot, float ox, float oy, float bw, float bh);
	~CatEntity() override;
	void Update(float) override;
	void Draw(sf::RenderWindow*) override;
};

