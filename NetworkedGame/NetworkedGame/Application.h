#pragma once

#include "SFML\Graphics.hpp"

#include "GameStateManager.h"
#include "AssetManager.h"
#include "InputHandler.h"
#include "Client.h"
#include "Timer.h"

#include "ArenaState.h"

class Application
{
public:
	Application(std::string title, int width, int height, int offsetX, int offsetY);
	~Application();
	
	void Update();
	void Draw();
	void CleanUp();
	bool IsRunning();
	void Pause(bool);
	bool Paused();
	void Exit();

	Client * client;
	AssetManager * assetManager;
	InputHandler * inputHandler;
	GameStateManager * gamestateManager;
	sf::FloatRect screenBounds;
protected:	
	Timer * _timer;	
	sf::RenderWindow * _render_window;	
	sf::View * _view;
	bool _running;
	bool _paused;
	bool _debug_mode = false;
};

