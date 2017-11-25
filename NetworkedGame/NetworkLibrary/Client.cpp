#include "Client.h"

Client::Client(sf::TcpSocket * socket, sf::Int32 id)
{
	_tcp_socket = socket;
	_id = id;
}
Client::~Client()
{
}