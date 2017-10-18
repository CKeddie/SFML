#pragma once
#include "Component.h"

class Entity;

class Collider :
	public Component
{
public:
	Collider(Entity & entity);
	~Collider();
	void Update(float) override;
	void Draw(sf::RenderWindow*) override;
	virtual bool ResolveCollision(Collider col);
	float GetMax(sf::Vector2f axis);
	float GetMin(sf::Vector2f axis);
	sf::Vector2f* GetVertices();
	void SetVertices(sf::Vector2f*, int count);
	sf::Vector2f GetVertex(int i);
	int GetVertexCount() { return _vertex_count; }
protected:
	float IntervalDistance(float minA, float maxA, float minB, float maxB);
	sf::VertexArray _debug_vertices;
	sf::Vector2f * _vertices;
	int _vertex_count;
};

