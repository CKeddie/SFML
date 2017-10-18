#include "Collider.h"

#include "Entity.h"
#include "MathsExt.h"

Collider::Collider(Entity & entity)
	: Component(entity)
{

}

Collider::~Collider()
{
}

void Collider::Update(float)
{
	for (unsigned int i = 0; i < _debug_vertices.getVertexCount(); i++)
	{
		if (_vertices)
			_debug_vertices[i].position = _entity.Position() + _vertices[i];
	}
}

void Collider::Draw(sf::RenderWindow * window)
{
	//if(_debug_mode)
		window->draw(_debug_vertices);
}

bool Collider::ResolveCollision(Collider col)
{
	float x_min_a = GetMin(sf::Vector2f(1, 0));
	float x_max_a = GetMax(sf::Vector2f(1, 0));
	float y_min_a = GetMin(sf::Vector2f(0, 1));
	float y_max_a = GetMax(sf::Vector2f(0, 1));

	float x_min_b = col.GetMin(sf::Vector2f(1, 0));
	float x_max_b = col.GetMax(sf::Vector2f(1, 0));
	float y_min_b = col.GetMin(sf::Vector2f(0, 1));
	float y_max_b = col.GetMax(sf::Vector2f(0, 1));

	if (IntervalDistance(x_min_a, x_max_a, x_min_b, x_max_b) > 0)
		return false;	
}

float Collider::GetMax(sf::Vector2f axis)
{
	if (!_vertices)
	{
		std::cout << " vertices not initialized" << std::endl << std::endl;
		return 0;
	}

	float max = me::Dot(_entity.Position() + _vertices[0], axis);

	for (unsigned int i = 0; i < _vertex_count; i++)
	{
		float curr = me::Dot(_entity.Position() + _vertices[i], axis);
		if (curr > max)
			max = curr;
	}
	return max;
}


float Collider::GetMin(sf::Vector2f axis)
{
	if (!_vertices)
	{
		std::cout << " vertices not initialized" << std::endl << std::endl;
		return 0;
	}

	float min = me::Dot(_entity.Position() + _vertices[0], axis);

	for (int i = 0; i < _vertex_count; i++)
	{
		float curr = me::Dot(_entity.Position() + _vertices[i], axis);
		if (curr < min)
			min = curr;
	}
	return min;
}

sf::Vector2f * Collider::GetVertices()
{
	return _vertices;
}

void Collider::SetVertices(sf::Vector2f * vertices, int count)
{
	_vertices = vertices;
	_vertex_count = count;
}

sf::Vector2f Collider::GetVertex(int i)
{
	return _entity.Position() + _vertices[i];
}

float Collider::IntervalDistance(float minA, float maxA, float minB, float maxB)
{	
	if (minA < minB) 
	{
		return minB - maxA;
	}
	else 
	{
		return minA - maxB;
	}
}