#pragma once
#include "SFML\Network.hpp"
#include <string>
class Client
{
public:
	Client(std::string profileName);
	~Client();
	virtual	void Connect(sf::IpAddress ip, int port);
	virtual void Disconnect();
	virtual void SendTCP(sf::Packet sentData);
	virtual void SendUDP(sf::Packet packet);
	virtual void Receive(sf::Packet receivedData);
	std::string _profile_name;
	int _client_id;
protected:
	int _server_port;
	sf::IpAddress _server_ip;
	sf::UdpSocket * _udp_socket;
	sf::TcpSocket * _tcp_socket;
};
