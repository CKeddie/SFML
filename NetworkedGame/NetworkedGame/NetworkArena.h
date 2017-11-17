#pragma once
#include "ArenaState.h"
#include "../Server/Client.h"

class NetworkArena 
	: public ArenaState
{
public:
	NetworkArena(Application & app);
	~NetworkArena();
private:
	Client * _player_client;
};

