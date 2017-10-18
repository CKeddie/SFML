#pragma once
#include "Game.h"
#include "SFML\Network.hpp"

class Client;

class Server
	: public Application
{
public:

	Server();
	~Server();
	void Update() override;
	void CleanUp() override;
	void Listen();
private:
	sf::IpAddress _global_ip;
	sf::IpAddress _local_ip;

	sf::TcpSocket _tcp_socket;
	sf::UdpSocket _udp_socket;
	
	sf::TcpListener _tcp_listener;

	int _server_port = 5555;
	sf::Thread _listening_thread;
};

