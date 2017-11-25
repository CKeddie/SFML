#include <SFML/Graphics.hpp>

#include "Server.h"

Server * _server;

int main()
{
	_server = new Server();
	_server->Run();
	return 0;
}