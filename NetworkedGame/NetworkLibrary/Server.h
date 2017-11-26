#pragma once
#include "Client.h"
#include "IObserver.h"

#include "SFML\Network.hpp"

#include <iostream>
#include <memory>
#include <vector>
#include <string>

class Server
{
private:	
	enum TransportType
	{
		TCP,
		UDP
	};
	enum InstructionSet
	{
		RequestConnect,
		NotifyDisconnect,
		RequestPlayers,
		NotifyClients,
	};
public:
	Server(unsigned short port = 45000);
	~Server();
	void CleanUp();
	void Run();
	void Recieve();
	void HandlePacket(sf::Packet incomingPacket, int socketID);
	void SendPacketAll(sf::Packet packet, int clientException = -1);
	void SendPacket(sf::Packet packet, int client);
private:
	bool _isRunning = true;

	sf::IpAddress _ipAdress;
	unsigned short _port;

	sf::TcpListener _listener;
	sf::SocketSelector _selector;

	int _maxPlayerNumber;
	int _currentID;
	int _clientCount;

	std::vector<Client*> _clients;
	sf::Clock m_clock;
};

