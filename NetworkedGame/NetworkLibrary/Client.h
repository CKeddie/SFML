#pragma once
#include "IObserver.h"
#include <SFML/System/Vector2.hpp>
#include <SFML/Network.hpp>
#include <string>
#include <vector>
#include <memory>
#include <string>
#include <iostream>

class Client
{
public: 
	Client(sf::TcpSocket * socket, sf::Int32 id);
	~Client();

	sf::Int32 GetID() { return _id; }
	void SetName(const std::string name) { _name = name; }
	std::string GetName() { return _name; }

	sf::TcpSocket * GetTcpSocket() { return _tcp_socket; };
	sf::UdpSocket * GetUdpSocket() { return _udp_socket; };
	
	void SetTimeout(sf::Time time) { _timeout = time; }
	sf::Time GetTimeout() { return _timeout; }
protected:
	sf::Int32 _id = 0;
	sf::Int32 _authority = 1;
	std::string _name;
	sf::TcpSocket * _tcp_socket;
	sf::UdpSocket * _udp_socket;
	sf::Time _timeout;
};