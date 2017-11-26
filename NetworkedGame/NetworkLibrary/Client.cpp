#include "Client.h"

Client::Client(sf::TcpSocket * socket, sf::Int32 id)
{
	_tcp_socket = socket;
	_udp_socket = new sf::UdpSocket();
	_id = id;
}
Client::~Client()
{
}