#include <SFML/Graphics.hpp>
#include "CatFighterGame.h"
#include "Server.h"
#include "Client.h"
#include <iostream>

#include "SFML\System\Thread.hpp"

std::string _game_name = "Cat Fighter!";
CatFighterGame* _game;
Server * _server;
Client * _client;
int main()
{
	std::cout << "Initializing a new game " << _game_name << std::endl;

	_game = new CatFighterGame(_game_name, 1024, 720, 512 - 16, 360 - 16);
	_server = new Server();
	_client = new Client();
	std::cout << "Game Initialized. Running. " << std::endl;
	_client->Connect("127.0.0.1", 5555);
	
	while (_game->IsRunning())
	{
		if (_game->GetInputHandler()->IsKeyPressed(sf::Keyboard::Key::Escape))
			_game->Exit();
		//_game->Update();
		//_game->Draw();
	}

	std::cout << "Game finished. Exiting." << std::endl;

	return 0;
}