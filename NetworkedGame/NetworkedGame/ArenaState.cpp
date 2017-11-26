#include "ArenaState.h"
#include "GUILabel.h"
#include "Application.h"
#include "LocalPlayer.h"

ArenaState::ArenaState(Application & app)
	: GameState(app)
{
	//Set Spawn Points: Max 4 Players//
	_spawn_points.push_back(sf::Vector2f(2 * 32, 18 * 32));
	_spawn_points.push_back(sf::Vector2f(8 * 32, 12 * 32));
	_spawn_points.push_back(sf::Vector2f(29 * 32, 18 * 32));
	_spawn_points.push_back(sf::Vector2f(22 * 32, 12 * 32));

	//Load Textures//
	AppRef.assetManager->LoadTexture("platformer_tileset.png");
	AppRef.assetManager->LoadTexture("catFighter.png");
	AppRef.assetManager->LoadTexture("TilemapDebug.png");
	
	//Construct Tilesets//
	tileset = new Tileset(32, 32, AppRef.assetManager->GetTexture("platformer_tileset"));
	debug_tileset = new Tileset(32, 32, AppRef.assetManager->GetTexture("TilemapDebug"));

	//Initialize Entities//
	sf::Sprite * catSprite = AppRef.assetManager->TextureToSprite("catFighter", 64, 64);

	//Construct Map//(w, h, rw, rh)
	world = new Map(32, 23, 32, 32);
	
	//Load Tile Maps//
	world->LoadLayer("../Assets/cf_map_Backdrop.csv");
	world->LoadLayer("../Assets/cf_map_Background.csv");
	world->LoadLayer("../Assets/cf_map_Foreground.csv");
	world->LoadLayer("../Assets/cf_map_Foreground2.csv");
	
	//Load Collision Map//
	world->LoadCollisionMap("../Assets/cf_map_CollisionLayer.csv");
	
	//Load Tilesets//
	world->SetTileset(tileset);
	world->LoadDebugTileset(debug_tileset);

	//Initialize local player
	_local_player = new LocalPlayer(
		"Default"
		, 0
		, *AppRef.inputHandler);
}

void ArenaState::SpawnLocalPlayer()
{
	_local_player->CreateEntity(playerSprite, *world, _spawn_points[0]);
}

ArenaState::~ArenaState()
{
}

void ArenaState::Update(float dt)
{
	GameState::Update(dt);
	if (AppRef.inputHandler->IsKeyPressed(sf::Keyboard::Key::P))
	{
		if (AppRef.Paused())
			AppRef.Pause(false);
		else
			AppRef.Pause(true);
	}

	if (AppRef.Paused()) return;

	
	for (auto & player : _players)
		player.second->Update(dt);

	world->Update(dt);	

	AppRef.networkHandler->Receive();
}

void ArenaState::Draw(sf::RenderWindow * renderWindow)
{
	GameState::Draw(renderWindow);

	world->Draw(renderWindow);

	for (auto & player : _players)
		player.second->Draw(renderWindow);

	_control_manager->Draw(renderWindow);

	renderWindow->display();
}

void ArenaState::OnNotify(sf::Packet* inputPacket)
{
	sf::Int32 playerID;
	*inputPacket >> playerID;

	if (!_players[playerID])
	{
		_players[playerID] = new Player("", playerID);
		_players[playerID]->CreateEntity(
			AppRef.assetManager->TextureToSprite("catFighter", 64, 64)
			, *world
			, _spawn_points[playerID]);
	}

	if (_players[playerID])
	{
		sf::Vector2f p;
		*inputPacket >> p.x >> p.y;
		_players[playerID]->GetEntity()->SetPosition(p);
	}
}