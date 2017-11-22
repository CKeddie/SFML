#pragma once

#include "SFML\Graphics.hpp"
#include "Component.h"

class SpriteRenderer :
	public Component
{
public:
	enum Direction
	{
		Left = -1,
		Right = 1,
	};
	SpriteRenderer(Entity & entity, sf::Vector2f & position);
	~SpriteRenderer();
	void Update(float) override;
	void Draw(sf::RenderWindow*) override;
	void SetColour(sf::Uint32 colour);
	void SetSprite(sf::Sprite);
	void SetSpriteRect(sf::IntRect);
	void SetDirection(int dir);
	void SetDirection(Direction dir);
private:
	Direction _direction = Right;
	sf::Vector2f * _size;
	sf::Sprite* _sprite;
	sf::FloatRect _sourceRect;
};

