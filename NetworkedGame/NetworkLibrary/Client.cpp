#include "Client.h"
#include <iostream>

Client::Client(std::string profileName)
{
	_profile_name = profileName; 
	_tcp_socket = new sf::TcpSocket();
	_udp_socket = new sf::UdpSocket();
}

Client::~Client()
{

}

void Client::Connect(sf::IpAddress ip, int port)
{
	sf::Mutex m;
	m.lock();
	_server_ip = ip;
	_server_port = port;
	std::cout << "Connecting to: " << _server_ip << ":" << _server_port << std::endl;
	sf::Socket::Status status = _tcp_socket->connect(_server_ip, _server_port);
	switch (status)
	{
	case sf::Socket::Done:
		std::cout
			<< "Connected to server at ("
			<< _tcp_socket->getRemoteAddress() << ":"
			<< _tcp_socket->getRemotePort() << ")"
			<< std::endl;
		break;
	default:
		std::cout << "Failed to connect to: " << _server_ip << ":" << _server_port << std::endl;
		return;
	}

	if (_udp_socket->bind(_server_port) != sf::Socket::Done)
		std::cout << "Failed to bind UDP socket to port: " << _server_port << std::endl;

	std::cout << "UDP socket bound to port: " << _server_port << std::endl;

	m.unlock();
}

void Client::Disconnect()
{
	_send_thread->wait();
	std::cout << "TCP Socket disconnected from: " << _server_ip << ":" << _server_port << std::endl;
	_tcp_socket->disconnect();
	std::cout << "UDP Socket unbound from port: " << _server_port << std::endl;
	_udp_socket->unbind();
}

void Client::SendTCP(sf::Packet packet)
{
	std::cout << "Sending data packet: " << packet.getData() << ": " << packet.getDataSize() << std::endl;
	if (_tcp_socket->send(packet) != sf::Socket::Done)
	{
		//error could not send packet
	}
}
void Client::SendUDP(sf::Packet packet)
{
	std::cout << "Sending data packet: " << packet.getData() << ": " << packet.getDataSize() << std::endl;
	if (_udp_socket->send(packet, _server_ip, _server_port) != sf::Socket::Done)
	{
		//error could not send packet
	}
}

void Client::Receive(sf::Packet packet)
{
	if (_tcp_socket->receive(packet) != sf::Socket::Done)
	{
		//error could not receive packet
	}
}

void Client::OnNotify(sf::Packet data)
{
	int i;
	data >> i;
	switch (i)
	{
	case 1:
		std::cout << "Sending via TCP" << std::endl;
		SendTCP(data);
		break;
	case 2:
		std::cout << "Sending via UDP" << std::endl;
		SendUDP(data);
		break;
	default:
		break;
	}
}