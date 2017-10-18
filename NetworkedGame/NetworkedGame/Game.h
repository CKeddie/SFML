#pragma once

#include "SFML\Graphics.hpp"
#include "Timer.h"
#include "AssetManager.h"
#include "InputHandler.h"

class Application
{
public:
	Application(std::string title, int width, int height, int offsetX, int offsetY);
	~Application();
	
	virtual void Update();
	virtual void Draw();
	virtual void CleanUp() = 0;
	bool IsRunning();
	void Exit();

	InputHandler* GetInputHandler();
protected:
	Timer* _timer;
	AssetManager* _assetManager;
	sf::RenderWindow* _renderWindow;
	InputHandler* _inputHandler;
	sf::View* _view;
	bool _isRunning;
};

