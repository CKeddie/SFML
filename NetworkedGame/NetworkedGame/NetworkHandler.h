#pragma once

#include "IObserver.h"
#include "ISubject.h"
#include "SFML\Network.hpp"
#include "Player.h"
#include <map>

class NetworkHandler
	: public IObserver<sf::Packet>
	, public ISubject<int>
{
private:
	enum TransportType
	{
		TCP,
		UDP,
	};
	enum InstructionSet
	{
		OnConnect,
		OnDisconnect,
		OnUpdatePlayers,
		OnCreatePlayers,
	};
public:
	NetworkHandler(std::string name, sf::IpAddress ip, unsigned short port);
	~NetworkHandler();
	void Connect();
	void Disconnect();
	void Send(sf::Packet p);
	void Receive();
	void OnNotify(sf::Packet) override;
	
	std::string GetName() { return _name; }
	int GetID() { return _clientID; }

private:
	void SortPacket(sf::Packet packet);
	bool _connected = false;
	std::string _name;
	sf::Int32 _clientID = 0;
	sf::Int32 _num_connections = 0;
	sf::TcpSocket * _socketTCP;
	sf::UdpSocket * _socketUDP;
	sf::IpAddress _address;
	unsigned short _port;
};

