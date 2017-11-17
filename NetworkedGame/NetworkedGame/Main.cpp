#include <SFML/Graphics.hpp>
#include <iostream>

#include "SFML\System\Thread.hpp"
#include "Application.h"

Application * _game;
std::string _game_name = "Cat Fighter!";

int main()
{
	std::cout << "Initializing a new game " << _game_name << std::endl;

	_game = new Application(_game_name, 1024, 720, 512 - 16, 360 - 16);

	std::cout << "Game Initialized. Running. " << std::endl;
	while (_game->IsRunning())
	{
		_game->Update();
		_game->Draw();
	}

	std::cout << "Game finished. Exiting." << std::endl;

	return 0;
}