#pragma once

#include "SFML\Graphics.hpp"

#include "GameStateManager.h"
#include "NetworkHandler.h"
#include "AssetManager.h"
#include "InputHandler.h"
#include "Client.h"
#include "ArenaState.h"

class Application
{
public:
	Application(std::string title, std::string clientName, float width, float height, float offsetX, float offsetY);
	~Application();
	
	void Update();
	void Draw();
	void CleanUp();
	bool IsRunning();
	void Pause(bool);
	bool Paused();
	void Exit();

	AssetManager * assetManager;
	InputHandler * inputHandler;
	GameStateManager * gamestateManager;
	NetworkHandler * networkHandler;
	sf::FloatRect screenBounds;
protected:	
	sf::Clock clock;
	sf::RenderWindow * _render_window;	
	sf::View * _view;
	bool _has_focus = true;
	bool _running;
	bool _paused;
	bool _debug_mode = true;
};

