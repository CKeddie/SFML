#include "Application.h"
#include "ArenaState.h"

Application::Application(std::string title, int width, int height, int offsetX, int offsetY)
{
	std::cout << "Application Initialized. Please provide profile name." << std::endl;
	
	std::string str;
	std::cin >> str;
	sf::TcpSocket * socket = new sf::TcpSocket();
	client = new Client(socket, 0);

	std::cout << "Welcome " << str << "." << std::endl;

	_running = true;
	_timer = new Timer();
	_view = new sf::View(sf::Vector2f(offsetX, offsetY), sf::Vector2f(width, height));
	screenBounds = sf::FloatRect(0, 0, width, height);
	_render_window = new sf::RenderWindow(sf::VideoMode(width, height), title);
	assetManager = new AssetManager("../Assets");
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

	//poll input events
	while (_render_window->pollEvent(_event))
	{
		inputHandler->HandleEvents(_event);
	}

	//exit application
	if (inputHandler->IsKeyPressed(sf::Keyboard::Key::Escape))
		Exit();

	//toggle global debug mode
	if (inputHandler->IsKeyPressed(sf::Keyboard::Key::F1))
		_debug_mode = !_debug_mode;
	
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