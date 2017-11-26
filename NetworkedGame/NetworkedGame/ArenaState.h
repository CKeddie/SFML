#pragma once


#include "GameState.h"
#include "CatEntity.h"
#include "Tileset.h"
#include "Map.h"
#include "LocalPlayer.h"

#include "ISubject.h"

class ArenaState
	: public GameState
	, public IObserver<sf::Packet*>
{
public:
	ArenaState(Application & app);
	void SpawnLocalPlayer();
	~ArenaState();
	void Update(float) override;
	void Draw(sf::RenderWindow*) override;
	void OnNotify(sf::Packet*) override;
protected:
	LocalPlayer * _local_player;
	std::map<int, Player*> _players;
	std::vector<sf::Vector2f> _spawn_points;
	Tileset* tileset;
	Tileset* debug_tileset;
	Map* world;
	sf::Sprite* playerSprite;
};

