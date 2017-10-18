#include "Client.h"
#include <iostream>
Client::Client()
{
	
}


Client::~Client()
{
}

void Client::Connect(std::string ip, int port)
{
	_server_ip = sf::IpAddress(ip);
	std::cout << "Connecting to: " << _server_ip << ":" << _server_port << std::endl;
	
	if (_tcp_socket.connect(_server_ip, _server_port) != sf::Socket::Done)
	{
		//error...
		std::cout << "Failed to connect to: " << _server_ip << ":" << _server_port << std::endl;
	}
	std::cout << "Connected to server at(" << _tcp_socket.getRemoteAddress() << ":" << _tcp_socket.getRemotePort() << ")" << std::endl;
}

void Client::Disconnect()
{

}

//void Client::Connect(std::string ip, int port)
//{
//	
//}
//
//size_t Client::Send(char * buffer, size_t len)
//{
//	return size_t();
//}
//
//size_t Client::Receive(char * buffer, size_t len)
//{
//	return size_t();
//}
//
//std::string Client::GetIP()
//{
//	return std::string();
//}
//
//int Client::GetPort()
//{
//	return 0;
//}
