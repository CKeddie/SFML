#pragma once

#include "IObserver.h"
#include "SFML\Network.hpp"
#include "ArenaState.h"
#include <map>

class NetworkHandler 
	: public ArenaState
	, public IObserver<sf::Packet>
{
public:
	enum TransportType
	{
		TCP,
		UDP,
	};
	enum InstructionSet
	{
		RequestConnect,
		NotifyDisconnect,
		RequestPlayers,
		NotifyClients,
	};
public:
	NetworkHandler(std::string name, sf::IpAddress ip, unsigned short port, Application & application);
	void SpawnLocalPlayer();
	~NetworkHandler();
	void Connect();
	void Disconnect();
	void Send(sf::Packet p);
	void Receive();
	void OnNotify(sf::Packet packet) override;
	void Update(float) override;
	void Draw(sf::RenderWindow*) override;

	std::string GetName() { return _name; }
	int GetID() { return _clientID; }

private:
	bool _connected = false;
	std::string _name;
	sf::Int32 _clientID = 0;
	sf::Int32 _num_connections = 0;
	sf::TcpSocket * _socketTCP;
	sf::UdpSocket * _socketUDP;
	sf::IpAddress _address;
	unsigned short _port;
	//sf::Thread _receiver;
};

