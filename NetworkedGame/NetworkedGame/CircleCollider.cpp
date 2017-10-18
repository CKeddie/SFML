#include "CircleCollider.h"



CircleCollider::CircleCollider(Entity & entity, int radius, int resolution) 
	: Collider(entity)
{

}

CircleCollider::~CircleCollider()
{
	Collider::~Collider();
}

void CircleCollider::Update(float deltaTime)
{
	Collider::Update(deltaTime);
}

void CircleCollider::Draw(sf::RenderWindow * window)
{
	Collider::Draw(window);
}
