#pragma once

#include "Entity.h"
#include "SpriteRenderer.h"
#include "BoxCollider.h"
#include "PhysicsBody.h"
#include "SFML\Network.hpp"

struct CatData
{
	sf::Vector2f velocity;
	sf::Vector2f position;

};
//
//sf::Packet& operator << (sf::Packet& packet, const CatData& catData)
//{
//	return packet << catData.position << catData.velocity;
//}


class CatEntity 
	: public Entity
{
public:
	enum Animations
	{
		Idle,
		Run,
		Jump,
		Fall,
	};

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

