#include <SFML/Graphics.hpp>

#include "Server.h"

Server * _server;

int main()
{
	_server = new Server(sf::IpAddress::getLocalAddress(), 5555);

	while (true)
	{
		//Hang
	}

	return 0;
}