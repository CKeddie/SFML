#include "Server.h"
#include "Client.h"

Server::Server(sf::IpAddress address, int port)
	: _listening_thread(&Server::Listener, this)
	, _sender_reciever_thread(&Server::Reciever, this)
{
	_server_ip = address;
	_server_port = port;
	std::cout << "Initialized Server" << std::endl;
	std::cout << "Address: "<< _server_ip << std::endl;

	_tcp_listener.listen(_server_port);
	_socket_selector.add(_tcp_listener);
	
	_listening_thread.launch();
	_sender_reciever_thread.launch();
}


Server::~Server()
{
	//_listening_thread.terminate();
	//_sender_reciever_thread.terminate();
}

void Server::Update()
{

}

void Server::CleanUp()
{
}

void Server::Reciever()
{
	sf::Mutex m;
	while (true)
	{
		if (_socket_selector.wait())
		{
			m.lock();
			for (std::vector<sf::TcpSocket*>::size_type i = 0; i != _tcp_connections.size(); i++)
			{
				if (_socket_selector.isReady(*_tcp_connections[i]))
				{
					std::cout << "Connection ready." << std::endl;
					sf::Packet data;
					if (_tcp_connections[i]->receive(data) != sf::Socket::Done)
					{
						continue;
					}
					std::string s;
					data >> s;
					std::cout << s << std::endl;
					std::cout << "Received Data: " << s << std::endl;
				}

			}
			m.unlock();
		}
	}
}

void Server::ExecutionThread()
{
	//Initialize();
	//while (!_time_stop) Update();
	//CleanUp();
}

void Server::Listener()
{
	while (true)
	{
		sf::Mutex m;
		m.lock();
		std::cout << "Listening on port: " << _server_port << std::endl;
		if (_tcp_listener.listen(_server_port) != sf::Socket::Done)
		{
			std::cout << "Could not listen on port: " << _server_port << " may be in use." << std::endl;
			return;
		}

		sf::TcpSocket * client = new sf::TcpSocket();
		if (_tcp_listener.accept(*client) != sf::Socket::Done)
		{
			std::cout << "Could not accept client" << std::endl;
			return;
		}

		std::cout << "Accepted client: " << client->getRemoteAddress() << " - " << client->getLocalPort() << std::endl;
		_tcp_connections.push_back(client);
		_socket_selector.add(*client);
		m.unlock();
	}
}