#pragma once
#include "SFML\Graphics.hpp"
#include "GUIControlManager.h"

class Application;

class GameState
{
public:
	GameState(Application & app);
	~GameState();
	virtual void Update(float);
	virtual void Draw(sf::RenderWindow*);
protected:
	Application & AppRef;
	GUIControlManager * _control_manager;
};

