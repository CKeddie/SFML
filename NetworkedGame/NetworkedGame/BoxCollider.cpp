#include "BoxCollider.h"
#include "PhysicsBody.h"
#include "Entity.h"

BoxCollider::BoxCollider(Entity& entity, sf::Vector2f size, sf::Vector2f offset)
	: Collider(entity)
{
	//set up box size and offset from center
	_size = new sf::Vector2f(size);
	_offset = new sf::Vector2f(offset);


	//manually set up shape points
	_vertex_count = 4;
	_vertices = new sf::Vector2f[_vertex_count]
	{
		sf::Vector2f(-_size->x + _offset->x, -_size->y + _offset->y),
		sf::Vector2f(-_size->x + _offset->x,  _size->y + _offset->y),
		sf::Vector2f(_size->x + _offset->x,  _size->y + _offset->y),
		sf::Vector2f(_size->x + _offset->x, -_size->y + _offset->y)
	};

	//set up debug points for drawing
	_debug_vertices = sf::VertexArray(sf::Quads, 4);
	_debug_vertices[0].color = sf::Color::Green;
	_debug_vertices[1].color = sf::Color::Green;
	_debug_vertices[2].color = sf::Color::Green;
	_debug_vertices[3].color = sf::Color::Green;
}

BoxCollider::~BoxCollider()
{
	Collider::~Collider();
}

void BoxCollider::Update(float deltaTime)
{
	Collider::Update(deltaTime);
}

void BoxCollider::Draw(sf::RenderWindow * window)
{
	Collider::Draw(window);
}

void BoxCollider::SetSize(sf::Vector2f size)
{
	_size = new sf::Vector2f(size);
}

bool BoxCollider::ResolveCollision(Collider col)
{
	return false;
}

void BoxCollider::SetOffset(sf::Vector2f off)
{
	_offset = new sf::Vector2f(off);
}
