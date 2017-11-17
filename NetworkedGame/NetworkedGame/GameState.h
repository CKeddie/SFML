#pragma once
#include "SFML\Graphics\RenderWindow.hpp"
#include "Application.h"

class GameState
{
public:
	GameState(Application & app);
	~GameState();
	virtual void Update(float);
	virtual void Draw(sf::RenderWindow*);
protected:
	Application & AppRef;
};

