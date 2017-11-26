#include "NetworkHandler.h"
#include "Application.h"

NetworkHandler::NetworkHandler(std::string name, sf::IpAddress ip, unsigned short port, Application& application)
	: ArenaState(application)
	, IObserver<sf::Packet>()
	, _receiver(&NetworkHandler::Receive, this)
{
	_name = name;
	_address = ip;
	_port = port;
	_socketTCP = new sf::TcpSocket();
	_socketUDP = new sf::UdpSocket();
	//_receiver.launch();
	_local_player->Attach(this);
}

void NetworkHandler::SpawnLocalPlayer()
{
	_players[GetID()]->CreateEntity(playerSprite, *world, sf::Vector2f(2 * 32, 18 * 32));
}


NetworkHandler::~NetworkHandler()
{
}

void NetworkHandler::Connect()
{
	if (_connected) return;

	_socketTCP->setBlocking(true);
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
		request << static_cast<sf::Int32>(RequestConnect);
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
	_socketTCP->setBlocking(true);
	sf::Packet dcPacket;
	dcPacket << static_cast<sf::Int32>(TCP);
	dcPacket << static_cast<sf::Int32>(NotifyDisconnect);
	dcPacket << _clientID;
	Send(dcPacket);
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
	if (!_connected) return;
	sf::Packet inputPacket;

	_socketTCP->setBlocking(false);
	sf::Socket::Status status = _socketTCP->receive(inputPacket);

	//unpack instruction
	
	sf::Int32 transport;
	inputPacket >> transport;
	sf::Int32 type;
	inputPacket >> type;

	switch ((TransportType)type)
	{
	case NetworkHandler::RequestConnect:
	{
		//incoming packet should contain
		//unpack client id
		inputPacket >> _clientID;
		_local_player->SetID(_clientID);
		//unpack number of connections
		inputPacket >> _num_connections;

		sf::Packet out;
		//pack transport
		out << sf::Int32(TCP);

		//pack instruction 4 (Request Update)
		out << sf::Int32(RequestPlayers);

		Send(out);
		break;
	}
	//receive players
	case NetworkHandler::RequestPlayers:
	{
		//get player count
		//send request
		//get player id
		//get position/velocity
		//get player in game
		//set position/velocity
		break;
	}
	case NetworkHandler::NotifyClients:
	{
		//unpack id
		sf::Int32 clientID;
		inputPacket >> clientID;

		//if client does not exist
		if (!_players[clientID])
		{
			//map id and create new player
			_players[clientID] = new Player("Player", clientID);
			_players[clientID]->CreateEntity(playerSprite, *world, _spawn_points[clientID]);
		}

		//set position
		sf::Vector2f position;
		inputPacket >> position.x >> position.y;
		_players[clientID]->GetEntity()->SetPosition(position);
		break;
	}
	}
}

void NetworkHandler::OnNotify(sf::Packet packet)
{
	Send(packet);
}

void NetworkHandler::Update(float deltaTime)
{
	ArenaState::Update(deltaTime);

	//Connect LAN
	if (AppRef.inputHandler->IsKeyPressed(sf::Keyboard::Key::Insert))
		Connect();
	//Connect LAN
	if (AppRef.inputHandler->IsKeyPressed(sf::Keyboard::Key::Delete))
		Disconnect();

	Receive();
}

void NetworkHandler::Draw(sf::RenderWindow * renderWindow)
{
	ArenaState::Draw(renderWindow);
}
