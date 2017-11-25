#include "ArenaState.h"
#include "GUILabel.h"
#include "Application.h"
#include "LocalPlayer.h"

ArenaState::ArenaState(Application & app)
	: GameState(app)
{
	//Load Textures//
	
	AppRef.assetManager->LoadTexture("platformer_tileset.png");
	AppRef.assetManager->LoadTexture("catFighter.png");
	AppRef.assetManager->LoadTexture("TilemapDebug.png");
	
	//Construct Tilesets//
	tileset = new Tileset(32, 32, AppRef.assetManager->GetTexture("platformer_tileset"));
	debug_tileset = new Tileset(32, 32, AppRef.assetManager->GetTexture("TilemapDebug"));

	//Initialize Entities//
	sf::Sprite * catSprite = AppRef.assetManager->TextureToSprite("catFighter", 64, 64);

	//Construct Map//
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

	Player* _player = new LocalPlayer("Default", 0, *AppRef.inputHandler);
	_player->CreateEntity(catSprite, *world, sf::Vector2f(2*32,18*32));
	_players[_player->GetID()] = _player;
	_player->Attach(AppRef.networkHandler);

	_player = new Player("Default", 1);
	_player->CreateEntity(catSprite, *world, sf::Vector2f(29*32,18*32));
	_players[_player->GetID()] = _player;

	
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

	//Connect LAN
	if (AppRef.inputHandler->IsKeyPressed(sf::Keyboard::Key::Insert))
		AppRef.networkHandler->Connect();
	//Connect LAN
	if (AppRef.inputHandler->IsKeyPressed(sf::Keyboard::Key::Delete))
		AppRef.networkHandler->Disconnect();

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
