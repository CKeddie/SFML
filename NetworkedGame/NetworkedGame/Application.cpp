#include "Application.h"

#include "ArenaState.h"
Application::Application(std::string title, int width, int height, int offsetX, int offsetY)
{
	is_running = true;
	_timer = new Timer();
	_view = new sf::View(sf::Vector2f(offsetX, offsetY), sf::Vector2f(width, height));
	_render_window = new sf::RenderWindow(sf::VideoMode(width, height), title);
	assetManager = new AssetManager("Root");
	inputHandler = new InputHandler();
	gamestateManager = new GameStateManager();

	gamestateManager->PushState(new ArenaState(*this));
}


Application::~Application()
{
	delete _timer;
	_timer = nullptr;

	delete assetManager;
	assetManager = nullptr;

	delete gamestateManager;
	gamestateManager = nullptr;

	delete inputHandler;
	inputHandler = nullptr;
}

void Application::Update()
{
	inputHandler->Update();

	_timer->frame();

	sf::Event _event;

	while (_render_window->pollEvent(_event))
	{
		inputHandler->HandleEvents(_event);
	}

	if (inputHandler->IsKeyPressed(sf::Keyboard::Key::Escape))
		Exit();
	
	gamestateManager->Update(_timer->getTime());

}

void Application::Draw()
{
	_render_window->setView(*_view);
	gamestateManager->Draw(_render_window);
}

void Application::CleanUp()
{
	delete _timer;
	_timer = nullptr;
	delete assetManager;
	assetManager = nullptr;
	delete _render_window;
	_render_window = nullptr;
	delete inputHandler;
	inputHandler = nullptr;
	delete _view;
	_view = nullptr;
}

bool Application::IsRunning()
{
	return _render_window->isOpen() && is_running;
}

void Application::Pause(bool state)
{
	is_paused = state;
}

bool Application::Paused()
{
	return is_paused;
}

void Application::Exit()
{
	is_running = false;
}