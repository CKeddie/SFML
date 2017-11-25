#include <SFML/Graphics.hpp>
#include <iostream>

#include "SFML\System\Thread.hpp"
#include "Application.h"

Application * _game;
std::string _game_name = "Cat Fighter!";
std::string _player_name;

int main()
{
	std::cout << "Initializing a new game " << _game_name << std::endl;
	std::cout << "Set your client name..." << _game_name << std::endl;

	cin >> _player_name;

	_game = new Application(_game_name, _player_name, 1024.0f, 720.0f, 512.0f - 16.0f, 360.0f - 16.0f);

	std::cout << "Game Initialized. Running. " << std::endl;

	while (_game->IsRunning())
	{
		_game->Update();
		_game->Draw();
	}

	std::cout << "Game finished. Exiting." << std::endl;

	return 0;
}