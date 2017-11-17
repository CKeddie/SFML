#pragma once

#include "SFML\Graphics.hpp"

#include "Timer.h"
#include "AssetManager.h"
#include "InputHandler.h"
#include "GameStateManager.h"

class Application
{
public:
	Application(std::string title, int width, int height, int offsetX, int offsetY);
	~Application();
	
	virtual void Update();
	virtual void Draw();
	virtual void CleanUp();
	bool IsRunning();
	void Pause(bool);
	bool Paused();
	void Exit();

	AssetManager * assetManager;
	InputHandler * inputHandler;
	GameStateManager * gamestateManager;
protected:	
	Timer * _timer;	
	sf::RenderWindow * _render_window;	
	sf::View * _view;
	bool is_running;
	bool is_paused;
};

