#pragma once
#include "IObserver.h"
#include <SFML/System/Vector2.hpp>
#include <SFML/Network/TcpSocket.hpp>

#include <string>
#include <vector>
#include <memory>
#include <string>
#include <iostream>

class Client
{
public: 
	Client(sf::TcpSocket * socket, int id);
	~Client();

	int GetID() { return _id; }
	void SetName(const std::string name) { _name = name; }

	sf::TcpSocket * GetTcpSocket() { return _tcp_socket; };

	void SetTimeout(sf::Time time) { _timeout = time; }
	sf::Time GetTimeout() { return _timeout; }
protected:
	int _id = 0;
	int _authority = 1;
	std::string _name;
	sf::TcpSocket * _tcp_socket;
	sf::Time _timeout;
};