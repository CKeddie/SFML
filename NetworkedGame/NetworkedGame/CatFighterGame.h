#pragma once
#include "Game.h"
#include "CatEntity.h"
#include "Tileset.h"
#include "MapLayer.h"
#include "BoxCollider.h"
#include "PhysicsBody.h"

class CatFighterGame :
	public Application
{
public:
	CatFighterGame(std::string title, int width, int height, int offX, int offY);
	~CatFighterGame();
	void Update()  override;
	void CleanUp() override;
	void Draw()   override;
private:
	CatEntity* cat;
	Tileset* tileset;
	Tileset* debug_tileset;
	Map* world;
	sf::Sprite* sprite;
};

