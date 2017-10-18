#pragma once

#include "SFML\Graphics.hpp"

class Entity;

class Component
{
public:
	Component(Entity &);
	virtual ~Component() = default;
	virtual void Update(float) = 0;
	virtual void Draw(sf::RenderWindow*) = 0;
	virtual void SetDebugMode(bool mode) 
	{ _debug_mode = mode; }

protected:
	Entity& _entity;
	bool _debug_mode = false;
};

