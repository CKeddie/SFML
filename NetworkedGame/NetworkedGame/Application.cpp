#include "Application.h"
#include "ArenaState.h"
#include "NetworkHandler.h"

Application::Application(std::string title, std::string clientName, float width, float height, float offsetX, float offsetY)
{
	std::cout << "Application Initialized. Please provide profile name." << std::endl;
	
	_running = true;
	_view = new sf::View(sf::Vector2f(offsetX, offsetY), sf::Vector2f(width, height));
	screenBounds = sf::FloatRect(0, 0, width, height);
	_render_window = new sf::RenderWindow(sf::VideoMode(width, height), title);
	assetManager = new AssetManager("../Assets");
	inputHandler = new InputHandler();
	gamestateManager = new GameStateManager();
	gamestateManager->PushState(new NetworkHandler(clientName, sf::IpAddress::getPublicAddress(), 47000, *this));
}

Application::~Application()
{
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
	sf::Event event;

	//poll input events
	while (_render_window->pollEvent(event))
	{		
		if (event.type == sf::Event::GainedFocus)
			_has_focus = true;
		else if (event.type == sf::Event::LostFocus)
			_has_focus = false;
		
		if(_has_focus) inputHandler->HandleEvents(event);
	}

	//exit application
	if (inputHandler->IsKeyPressed(sf::Keyboard::Key::Escape))
		Exit();

	//toggle global debug mode
	if (inputHandler->IsKeyPressed(sf::Keyboard::Key::F1))
		_debug_mode = !_debug_mode;
	
	sf::Time deltaTime = clock.restart();
	gamestateManager->Update(deltaTime.asSeconds());

}

void Application::Draw()
{
	clock.restart();
	_render_window->setView(*_view);
	gamestateManager->Draw(_render_window);
}

void Application::CleanUp()
{
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
	return _render_window->isOpen() && _running;
}

void Application::Pause(bool state)
{
	_paused = state;
}

bool Application::Paused()
{
	return _paused;
}

void Application::Exit()
{
	_running = false;
}