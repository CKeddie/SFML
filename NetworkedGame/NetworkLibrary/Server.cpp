#include "Server.h"
//#include "Client.h"


Server::Server(sf::IpAddress address, int port)
	//: _listening_thread(&Server::Listen, this)
	//, _sender_reciever_thread(&Server::Recieve, this)
{
	_server_ip = address;
	_server_port = port;
	std::cout << "Initialized Server" << std::endl;
	std::cout << "Address: " << _server_ip << std::endl;
	std::cout << "Port: " << _server_port << std::endl;

	_tcp_listener.listen(_server_port);
	_socket_selector.add(_tcp_listener);
	
	//_listening_thread.launch();
	//_sender_reciever_thread.launch();
}


Server::~Server()
{
	//_listening_thread.terminate();
	//_sender_reciever_thread.terminate();
}

void Server::CleanUp()
{
}

void Server::Recieve()
{
}

//void Server::Recieve()
//{
//	sf::Mutex m;
//	while (true)
//	{
//		if (_socket_selector.wait())
//		{
//			m.lock();
//			for (std::vector<sf::TcpSocket*>::size_type i = 0; i != _clients.size(); i++)
//			{
//				if (_socket_selector.isReady(_clients[i].))
//				{
//					std::cout << "Connection ready." << std::endl;
//					sf::Packet data;
//					if (_clients[i].getTcpSocket().receive(data) != sf::Socket::Done)
//					{
//						continue;
//					}
//					std::string s;
//					data >> s;
//					std::cout << s << std::endl;
//					std::cout << "Received Data: " << s << std::endl;
//				}
//
//			}
//			m.unlock();
//		}
//	}
//}

void Server::Execute()
{
	while (true)
	{
		if (_socket_selector.wait())
		{
			if (_socket_selector.isReady(_tcp_listener))
			{
				sf::TcpSocket tempSocket;

				if (_tcp_listener.accept(tempSocket) == sf::Socket::Done)
				{
					_clients.push_back(new Client(&tempSocket, _clientID));
					std::cout << "Client connected from Address:"
						<< tempSocket.getRemoteAddress()
						<< ", Port: "
						<<tempSocket.getLocalPort() << std::endl;
					
					
					_socket_selector.add(*_clients.back()->GetTcpSocket());
					
					_clientCount++;
					
					sf::Packet welcomePacket;
					welcomePacket << 0;//instruction
					welcomePacket << _clientID;

					if (_clients.back()->GetTcpSocket()->send(welcomePacket) != sf::Socket::Done)
						std::cout << "Error: could not send packet." << std::endl;
					else
						std::cout << "Successfully send data packet" << std::endl;
					_clientID++;
				}
				else
				{
					for (int i = 0; i < _clients.size(); i++)
					{
						if (_socket_selector.isReady(*_clients[i]->GetTcpSocket()))
						{
							sf::Packet received;
							
							if (_clients[i]->GetTcpSocket()->receive(received) != sf::Socket::Done)
							{
								int num, id;
								received >> num;
								received >> id;

								if (num == 1)
								{
									
								}
							}
							//set timeout

						}
					}
				}
			}
		}
	}
}

void Server::Listen()
{
	while (true)
	{
		sf::Mutex m;
		m.lock();
		std::cout << "Listening on port: " << _server_port << std::endl;
		if (_tcp_listener.listen(_server_port) != sf::Socket::Done)
		{
			std::cout << "Could not listen on port: " << _server_port << " may be in use." << std::endl;
			return;
		}

		sf::TcpSocket client;// = new sf::TcpSocket();
		if (_tcp_listener.accept(client) != sf::Socket::Done)
		{
			std::cout << "Could not accept client" << std::endl;
			return;
		}

		std::cout << "Accepted client: " << client.getRemoteAddress() << " - " << client.getLocalPort() << std::endl;
		//_clients.push_back(client);
		_socket_selector.add(client);
		m.unlock();
	}
}

void Server::SendPacket(sf::Packet packet, int clientException)
{
	for (int i = 0; i < _clients.size(); i++)
	{
		if (clientException == i) continue;

		if (_clients[i]->GetTcpSocket()->send(packet) != sf::Socket::Done)
		{
			printf("Error: client %i could not send packet", i);
		}
	}
}