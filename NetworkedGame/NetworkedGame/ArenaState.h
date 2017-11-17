#pragma once

#include "SFML\Graphics.hpp"

#include "GameState.h"
#include "CatEntity.h"
#include "Tileset.h"
#include "Map.h"
#include "Player.h"

class ArenaState
	: public GameState
{
public:
	ArenaState(Application & app);
	~ArenaState();
	void Update(float) override;
	void Draw(sf::RenderWindow*)override;
private:
	int _num_players = 0;
	CatEntity* cat;
	Tileset* tileset;
	Tileset* debug_tileset;
	Map* world;
	sf::Sprite* sprite;
	Player* _player;
};

