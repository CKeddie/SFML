#pragma once
#include "SFML\Network.hpp"
#include <string>
class Client
{
public:
	Client();
	~Client();
	//	Client(int sd, struct sockaddr_in* address);
//	~Client();
	void Connect(std::string ip, int port);
	void Disconnect();
	sf::TcpSocket _tcp_socket;
	sf::IpAddress _server_ip;
	int _server_port = 5555;
//	virtual size_t Send(char * buffer, size_t len);
//	virtual size_t Receive(char * buffer, size_t len);
//	std::string GetIP();
//	int GetPort();
//private:
//	SOCKET	_socket;
//	sockaddr_in _addr;
//	std::string _client_ip;
//	int _client_port;
//	//friend class TCPAcceptor;
//	//friend class TCPConnection;
//	Client();
//	Client(const Client& client);
};

