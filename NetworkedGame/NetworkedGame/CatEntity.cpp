#include "CatEntity.h"

CatEntity::CatEntity(float px, float py, float sx, float sy, float rot, float ox, float oy, float bw, float bh)
	: CatEntity(sf::Vector2f(px, py), sf::Vector2f(sx, sy), rot, sf::Vector2f(ox, oy), sf::Vector2f(bw, bh))
{
}

CatEntity::CatEntity(sf::Vector2f position, sf::Vector2f scale, float rotation, sf::Vector2f boxOffset, sf::Vector2f boxSize)
	: Entity(position, scale, rotation)
{
	AddComponent(new BoxCollider(*this, boxSize, boxOffset));
	AddComponent(new PhysicsBody(*this));
	AddComponent(new SpriteRenderer(*this, *_position));
}

CatEntity::~CatEntity()
{
	Entity::~Entity();
}

void CatEntity::Update(float deltaTime)
{
	Entity::Update(deltaTime);
}

void CatEntity::Draw(sf::RenderWindow * window)
{
	Entity::Draw(window);
}