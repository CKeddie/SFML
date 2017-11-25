#pragma once


#include "GameState.h"
#include "CatEntity.h"
#include "Tileset.h"
#include "Map.h"
#include "LocalPlayer.h"

#include "ISubject.h"

class ArenaState
	: public GameState
	, public ISubject<sf::Packet>
{
public:
	ArenaState(Application & app);
	~ArenaState();
	void Update(float) override;
	void Draw(sf::RenderWindow*)override;
private:
	std::map<int, Player*> _players;
	Tileset* tileset;
	Tileset* debug_tileset;
	Map* world;
};

