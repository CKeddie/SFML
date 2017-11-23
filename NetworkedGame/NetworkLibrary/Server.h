#pragma once
#include "Client.h"
#include "IObserver.h"

#include "SFML\Network.hpp"

#include <iostream>
#include <memory>
#include <vector>
#include <string>

class Server
	//: public IObserver<sf::Packet>
{
public:

	Server(sf::IpAddress, int port);
	~Server();
	void CleanUp();
	void Recieve();
	void Execute();
	void Listen();
	void SendPacket(sf::Packet packet, int clientException);
	//void OnNotify(sf::Packet)override;
private:
	sf::IpAddress _server_ip;
		
	sf::TcpListener _tcp_listener;

	sf::SocketSelector _socket_selector;

	std::vector<Client*> _clients;

	unsigned short _server_port = 0;
	int _clientID, _clientCount;
	//sf::Thread _listening_thread;
	//sf::Thread _sender_reciever_thread;
};

