#include "Entity.h"

#include "SpriteRenderer.h"

Entity::Entity()
	//: IEntityData(*this)
{

}

Entity::Entity(sf::Vector2f position, sf::Vector2f scale, float rotation)
	: Entity()
{
	_position = new sf::Vector2f(position);
	_rotation = new float(rotation);
	_scale = new sf::Vector2f(scale);
	
}

Entity::Entity(float px, float py, float sx, float sy, float rot)
	: Entity(sf::Vector2f(px, py), sf::Vector2f(sx, sy), rot)
{

}

Entity::~Entity(void)
{
	for (auto &component : _components)
	{
		delete component.second;
		component.second = nullptr;
	}
}

void Entity::Update(float deltaTime)
{
	for (auto & component : _components)
		component.second->Update(deltaTime);
}

void Entity::Draw(sf::RenderWindow * window)
{
	for (auto & component : _components)
		component.second->Draw(window);
}

void Entity::AddComponent(Component * component)
{
	_components[&typeid(*component)] = component;
}