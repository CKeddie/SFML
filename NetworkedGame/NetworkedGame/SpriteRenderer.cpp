#include "SpriteRenderer.h"

#include "SFML\Graphics\RenderWindow.hpp"
#include "Entity.h"

SpriteRenderer::SpriteRenderer(Entity & entity, sf::Vector2f & position)
	: Component(entity)
{
}

SpriteRenderer::~SpriteRenderer()
{
	delete _size;
	_size = nullptr;
	delete _sprite;
	_sprite = nullptr;
}

void SpriteRenderer::Update(float deltaTime)
{
}

void SpriteRenderer::Draw(sf::RenderWindow * window)
{
	if (_sprite)
	{
		_sprite->setScale((int)_direction, 1);
		sf::Vector2f pos_dir;
		pos_dir.x = _size->x * (float)_direction;
		pos_dir.y = _size->y;
		_sprite->setPosition(_entity.Position() - pos_dir);
		window->draw(*_sprite);
	}
}

void SpriteRenderer::SetSprite(sf::Sprite sprite)
{
	_sprite = new sf::Sprite(sprite);
	_size = new sf::Vector2f(
		  (float)_sprite->getTextureRect().width / 2
		, (float)_sprite->getTextureRect().height / 2);
}

void SpriteRenderer::SetSpriteRect(sf::IntRect rect)
{	
	_sprite->setTextureRect(rect);
}

void SpriteRenderer::SetDirection(int dir)
{
	_direction = (Direction)dir;
}

void SpriteRenderer::SetDirection(Direction dir)
{
	_direction = dir;
}
