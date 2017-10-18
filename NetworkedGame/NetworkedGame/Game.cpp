#include "Game.h"

Application::Application(std::string title, int width, int height, int offsetX, int offsetY)
{
	_isRunning = true;
	_timer = new Timer();
	_view = new sf::View(sf::Vector2f(offsetX, offsetY), sf::Vector2f(width, height));
	_renderWindow = new sf::RenderWindow(sf::VideoMode(width, height), title);
	_assetManager = new AssetManager();
	_inputHandler = new InputHandler();
}


Application::~Application()
{
	delete _timer;
	_timer = nullptr;

	delete _assetManager;
	_assetManager = nullptr;
}

void Application::Update()
{
	_timer->frame();
	_inputHandler->Update();
	sf::Event _event;
	while (_renderWindow->pollEvent(_event))
	{
		_inputHandler->HandleEvents(_event);
	}
}

void Application::Draw()
{
	_renderWindow->setView(*_view);
}

bool Application::IsRunning()
{
	return _renderWindow->isOpen() && _isRunning;
}

void Application::Exit()
{
	_isRunning = false;
}

InputHandler * Application::GetInputHandler()
{
	return _inputHandler;
}
