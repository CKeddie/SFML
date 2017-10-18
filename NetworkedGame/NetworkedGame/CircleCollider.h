#pragma once
#include "Collider.h"
class CircleCollider :
	public Collider
{
public:
	CircleCollider(Entity & entity, int radius, int resolution = 16);
	~CircleCollider();
	void Update(float) override;
	void Draw(sf::RenderWindow*) override;
	
private:

};

