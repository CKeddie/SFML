#include "Client.h"
//Client::Client(std::string name)
//	: IObserver<sf::Packet>()
//{
//	_name = name;
//	_tcp_socket = std::make_unique<sf::TcpSocket>();
//	_udp_socket = std::make_unique<sf::UdpSocket>();
//}


Client::Client(sf::TcpSocket * socket, int id)
	//: IObserver<sf::Packet>()
{
	_tcp_socket = socket;
	//_udp_socket = std::make_unique<sf::UdpSocket>();
	_id = id;
}
Client::~Client()
{
}
//
//void Client::Connect(sf::IpAddress ip, int port)
//{
//	sf::Mutex m;
//	m.lock();
//	_server_ip = ip;
//	_server_port = port;
//	std::cout << "Connecting to: " << _server_ip << ":" << _server_port << std::endl;
//	sf::Socket::Status status = _tcp_socket.get()->connect(_server_ip, _server_port);
//	switch (status)
//	{
//	case sf::Socket::Done:
//		std::cout
//			<< "Connected to server at ("
//			<< _tcp_socket.get()->getRemoteAddress() << ":"
//			<< _tcp_socket.get()->getRemotePort() << ")"
//			<< std::endl;
//		break;
//	default:
//		std::cout << "Failed to connect to: " << _server_ip << ":" << _server_port << std::endl;
//		return;
//	}
//
//	if (_udp_socket.get()->bind(_server_port) != sf::Socket::Done)
//		std::cout << "Failed to bind UDP socket to port: " << _server_port << std::endl;
//
//	std::cout << "UDP socket bound to port: " << _server_port << std::endl;
//
//	m.unlock();
//}
//
//void Client::Connect()
//{
//	Connect(_server_ip, _server_port);
//}
//
//void Client::Disconnect()
//{
//	std::cout << "TCP Socket disconnected from: " << _server_ip << ":" << _server_port << std::endl;
//	//send data to server requesting a disconnect---------------------------------------------------------
//	_tcp_socket.get()->disconnect();
//	std::cout << "UDP Socket unbound from port: " << _server_port << std::endl;
//	_udp_socket.get()->unbind();}
//
//void Client::SendTCP(sf::Packet packet)
//{
//	std::cout << "Sending data packet: " << packet.getData() << ": " << packet.getDataSize() << std::endl;
//	if (_tcp_socket.get()->send(packet) != sf::Socket::Done)
//	{
//		//error could not send packet
//	}
//}
//void Client::SendUDP(sf::Packet packet)
//{
//	std::cout << "Sending data packet: " << packet.getData() << ": " << packet.getDataSize() << std::endl;
//	if (_udp_socket.get()->send(packet, _server_ip, _server_port) != sf::Socket::Done)
//	{
//		//error could not send packet
//	}
//}
//
//void Client::Receive(sf::Packet packet)
//{
//	if (_tcp_socket.get()->receive(packet) != sf::Socket::Done)
//	{
//		//error could not receive packet
//	}
//}
//
//void Client::OnNotify(sf::Packet data)
//{
//	int i;
//	data >> i;
//	switch (i)
//	{
//	case 1:
//		std::cout << "Sending via TCP" << std::endl;
//		SendTCP(data);
//		break;
//	case 2:
//		std::cout << "Sending via UDP" << std::endl;
//		SendUDP(data);
//		break;
//	default:
//		break;
//	}
//}