#include "Server.h"

Server::Server(unsigned short port)
{
	_port = port;

	std::cout << "Initialized Server" << std::endl;
	std::cout << "Port: " << _port << std::endl;

	_listener.listen(_port);
	_selector.add(_listener);
}


Server::~Server()
{
}

void Server::CleanUp()
{
}

void Server::Run()
{
	while (_isRunning)
	{
		if (_selector.wait())
		{
			if (_selector.isReady(_listener))
			{
				sf::TcpSocket * socket = new sf::TcpSocket();
				sf::Socket::Status status = _listener.accept(*socket);
				
				switch (status)
				{
				case sf::Socket::Done:
				{
					sf::Packet packet;
					if (socket->receive(packet) == sf::Socket::Done)
					{
						_clients.push_back(new Client(socket, _clientCount));
						_selector.add(*_clients.back()->GetTcpSocket());
						HandlePacket(packet, _clientCount);
						printf("Client[%i]: '%s' has connected.", _clientCount, _clients[_clientCount]->GetName());
						_clientCount++;
					}					
					break;
				}
				case sf::Socket::Error:
					std::cout << "Error: Could not accept client." << std::endl;
					break;
				}
				
			}
			else//Receive
			{
				Recieve();
			}
		}
	}
}


void Server::Recieve()
{
	for (int i = 0; i < _clients.size(); i++)
	{
		if (_selector.isReady(*_clients[i]->GetTcpSocket()))
		{
			sf::Packet received;
			if (_clients[i]->GetTcpSocket()->receive(received) == sf::Socket::Done)
			{
				HandlePacket(received, i);
			}
		}
	}
}

void Server::HandlePacket(sf::Packet incomingPacket, int socketID)
{
	sf::Int32 transport;
	sf::Int32 protocol;
	InstructionSet instruction;
	
	incomingPacket >> transport >> protocol;
	
	instruction = (InstructionSet)protocol;
	
	const char* message = "";
	sf::Packet outgoingPacket;

	switch (instruction)
	{
		case Server::OnConnect:
		{
			sf::String name;
			incomingPacket >> name;
			_clients[socketID]->SetName(name);

			message = "(WelcomePack)";
			outgoingPacket << (sf::Int8)OnConnect;
			outgoingPacket << socketID;
			outgoingPacket << _clients.size();
			SendPacket(outgoingPacket, socketID);
			break;
		}
	case Server::OnDisconnect:
		message = "(Disconnected)";
		_clients.erase(_clients.begin() + socketID);
		SendPacketAll(outgoingPacket, socketID);
		break;
	case Server::OnUpdatePlayers:
		break;
	case Server::OnCreatePlayers:
		SendPacketAll(outgoingPacket, socketID);
		break;
	}

	printf("Client: %i %s Instruction: %s",  socketID, message, instruction);
}

void Server::SendPacketAll(sf::Packet packet, int clientException = -1)
{
	for (int i = 0; i < _clients.size(); i++)
	{
		if (clientException == i) continue;

		SendPacket(packet, _clients[i]->GetID());
	}
}

void Server::SendPacket(sf::Packet packet, int id)
{
	if (_clients[id]->GetTcpSocket()->send(packet) != sf::Socket::Done)
	{
		printf("Error: could not send packet to client %i: %s", id, _clients[id]->GetName());
	}
}
