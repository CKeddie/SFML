#include "NetworkHandler.h"

NetworkHandler::NetworkHandler(std::string name, sf::IpAddress ip, unsigned short port)
	: IObserver<sf::Packet>()
	, ISubject<int>()
{
	_name = name;
	_address = ip;
	_port = port;
	_socketTCP = new sf::TcpSocket();
	_socketUDP = new sf::UdpSocket();
}


NetworkHandler::~NetworkHandler()
{
}

void NetworkHandler::Connect()
{
	if (_connected) return;

	//Connect to server
	sf::Socket::Status status = _socketTCP->connect(_address, _port);

	switch (status)
	{
	case sf::Socket::Done:
	{
		_connected = true;
		std::cout << "Successfully connected TCP socket to server.\nSending data.\n" << std::endl;
		
		//set up a server request for a player index and other client info
		sf::Packet request;
		sf::String name = _name;

		request << static_cast<sf::Int32>(TCP);
		request << static_cast<sf::Int32>(OnConnect);
		request << static_cast<sf::String>(name);
		
		//Send data request
		Send(request);

		//Bind udp
		status = _socketUDP->bind(_port);
		break;
	}
	case sf::Socket::Disconnected:
		std::cout << "Error: Client was disconnected." << std::endl;
		break;
	case sf::Socket::Error:
		std::cout << "Error: Could not connect." << std::endl;
		break;
	}

	switch (status)
	{
	case sf::Socket::Done:
	{
		std::cout << "Successfully connected UDP to port: " << _port << std::endl;
		break;
	}
	case sf::Socket::Disconnected:
	{
		std::cout << "Error: UDP socket was disconnected." << std::endl;
		break;
	}
	case sf::Socket::Error:
	{
		std::cout << "Error: Could not bind UDP Socket." << std::endl;
		break;
	}
	}
}


void NetworkHandler::Disconnect()
{
	sf::Packet dcPacket;
	dcPacket << (int)OnDisconnect;
	dcPacket << _clientID;
	Send(dcPacket);
	Receive();
	_socketTCP->disconnect();
	_socketUDP->unbind();
	_connected = false;
	printf("Client has been disconnected.\n\n");
}

void NetworkHandler::Send(sf::Packet p)
{
	if (!_connected) return;
	
	sf::Int32 value;

	p >> value;

	TransportType transport = (TransportType)value;
	sf::Socket::Status status = sf::Socket::Status::Disconnected;
	
	switch (transport)
	{
	case NetworkHandler::TCP:
		status = _socketTCP->send(p);
		break;
	case NetworkHandler::UDP:
		status = _socketUDP->send(p, _address, _port);
		break;
	}

	switch (status)
	{
	case sf::Socket::Done:
		printf("Packet was successfully send via: %s", transport);
		break;
	case sf::Socket::Disconnected:
		printf("Error: Packet sending was unsuccessful. Client was disconnected.");
		break;
	case sf::Socket::Error:
		printf("Error: Packet sending was unsuccessful.");
		break;
	}
}


void NetworkHandler::Receive()
{
	sf::Packet incoming;
	sf::Socket::Status status = _socketTCP->receive(incoming);

	switch (status)
	{
	case sf::Socket::Done:
		SortPacket(incoming);
		break;
	case sf::Socket::Error:
		break;
	}
}


void NetworkHandler::OnNotify(sf::Packet packet)
{
	//Send(packet);
}

void NetworkHandler::SortPacket(sf::Packet packet)
{
	int id;
	//unpack instruction
	packet >> id;
	InstructionSet instruction;
	instruction = (InstructionSet)id;

	switch (instruction)
	{
	case NetworkHandler::OnConnect:
	{
		//incoming packet should contain
		//unpack client id
		packet >> _clientID;

		//unpack number of connections
		packet >> _num_connections;

		sf::Packet out;
		//pack transport
		out << (int)TCP;
		//pack instruction 4 (Request Update)
		int i = (int)OnUpdatePlayers;
		out << i;
		Send(out);
		break;
	}
	case NetworkHandler::OnDisconnect:
		//safe to disconnect
		break;
	case NetworkHandler::OnUpdatePlayers:
		Notify(1);
		//get player id
		//get position/velocity
		//get player in game
		//set position/velocity
		break;
	case NetworkHandler::OnCreatePlayers:
		//unpack id
		//map id and create new player
		//create player entity
		Notify(0);
		break;
	}
}