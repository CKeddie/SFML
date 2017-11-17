#pragma once
#include "SFML\Network.hpp"
#include <iostream>

class Client;

class Server
{
public:

	Server();
	~Server();
	void Update();
	void CleanUp();
	void Reciever();
	void ExecutionThread();
	void Listener();
private:
	sf::IpAddress _server_ip;
	
	sf::TcpSocket _tcp_socket;
	sf::UdpSocket _udp_socket;
	
	sf::TcpListener _tcp_listener;

	sf::SocketSelector _socket_selector;
	std::vector<sf::TcpSocket*> _tcp_connections;

	int _server_port = 5555;
	sf::Thread _listening_thread;
	sf::Thread _sender_reciever_thread;
};

