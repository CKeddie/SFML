#pragma once
#include <string>
#include <vector>
#include "IObserver.h"
#include "SFML\Network.hpp"

class Client 
	: public IObserver<sf::Packet>

{
public:
	Client(std::string profileName = "");
	~Client();
	virtual	void Connect(sf::IpAddress ip, int port);
	virtual void Disconnect();
	virtual void SendTCP(sf::Packet sentData);
	virtual void SendUDP(sf::Packet packet);
	virtual void Receive(sf::Packet receivedData);
	void OnNotify(sf::Packet data) override;
	std::string _profile_name;
	int _client_id;
protected:
	int _server_port;
	sf::Thread * _send_thread;
	sf::IpAddress _server_ip;
	sf::UdpSocket * _udp_socket;
	sf::TcpSocket * _tcp_socket;
	std::vector<sf::Packet*> _packet_stream;
};
