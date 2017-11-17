#pragma once
#include "SFML\Graphics.hpp"
#include "SFML\Graphics\Shape.hpp"
#include "SFML\Graphics\Transform.hpp"
#include "Collider.h"
#include "CollisionLayer.h"

class CatEntity;

class BoxCollider 
	: public Collider
{
public:
	BoxCollider(Entity & entity, sf::Vector2f size, sf::Vector2f offset);
	~BoxCollider();

	void Update(float) override;
	void Draw(sf::RenderWindow* window) override;

	bool ResolveCollision(Collider col) override;
	void SetOffset(sf::Vector2f);
	void SetSize(sf::Vector2f);
	sf::Vector2f RectGetOffset() { return *_offset;	};
protected:
	sf::Vector2f* _size;
	sf::Vector2f* _offset;
};

