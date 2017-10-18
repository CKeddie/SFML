#include "Server.h"
#include "Client.h"

Server::Server()
	: Application("Game Server", 0, 0, 0, 0)
	, _listening_thread(&Server::Listen, this)
{
	_listening_thread.launch();
}


Server::~Server()
{
}

void Server::Update()
{ 
	Listen();
}

void Server::CleanUp()
{
}

void Server::Listen()
{
	std::cout << "Listening on port: " << _server_port << std::endl;
	if (_tcp_listener.listen(_server_port) != sf::Socket::Done)
	{
		std::cout << "Could not listen on port: " << _server_port << " may be in use." << std::endl;
	}
	sf::TcpSocket client;
	if (_tcp_listener.accept(client) != sf::Socket::Done)
	{
		std::cout << "Could not accept client" << std::endl;
	}
}
