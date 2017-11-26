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
						//add new client
						_clients.push_back(new Client(socket, _clientCount));
						//add client to selector
						_selector.add(*_clients.back()->GetTcpSocket());
						//receive packet
						HandlePacket(packet, _clientCount);
						//print client index and name
						printf("Client[%i]: '%s' has connected.\n"
							, _clientCount, _clients[_clientCount]->GetName().c_str());
						
						//increment count
						_clientCount++;

						sf::Packet outPacket;
						outPacket << static_cast<sf::Int32>(0);
						outPacket << static_cast<sf::Int32>(NotifyClients);
						outPacket << static_cast<sf::Int32>(_clientCount);
						SendPacketAll(outPacket);
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
			if(_clients[i]->UdpReceive())
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
		case Server::RequestConnect:
		{
			sf::String name;
			incomingPacket >> name;
			_clients[socketID]->SetName(name);

			message = "(WelcomePack)";

			outgoingPacket << static_cast<sf::Int32>(0);//transport tcp;
			outgoingPacket << static_cast<sf::Int32>(RequestConnect); //type
			outgoingPacket << static_cast<sf::Int32>(socketID); //client id
			outgoingPacket << static_cast<sf::Int32>(_clients.size()); //num clients
			SendPacket(outgoingPacket, socketID);
			break;
		}
	case Server::NotifyDisconnect:
		message = "(Disconnected)";
		_clients.erase(_clients.begin() + socketID);		
		for (int i = 0; i < _clients.size(); i++)
		{
			if (socketID == i) continue;

			SendPacket(incomingPacket, _clients[i]->GetID());
		}
		break;
	case Server::RequestPlayers:
		break;
	case Server::NotifyClients:
	{
		for (int i = 0; i < _clients.size(); i++)
		{
			if (socketID == i) continue;

			SendPacket(incomingPacket, _clients[i]->GetID());
		}
		break;
	}
	}

//	printf("Client: %i %s Instruction: %s",  socketID, message, instruction);
}

void Server::SendPacketAll(sf::Packet packet, int clientException)
{

}

void Server::SendPacket(sf::Packet packet, int id)
{
	if (_clients[id]->GetTcpSocket()->send(packet) != sf::Socket::Done)
	{
		printf("Error: could not send packet to client %i: %s \n", id, _clients[id]->GetName());
	}
}
