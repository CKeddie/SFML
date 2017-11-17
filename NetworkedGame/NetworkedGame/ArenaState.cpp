#include "ArenaState.h"



ArenaState::ArenaState(Application & app)
	: GameState(app)
{
	//Load Textures/k/
	
	AppRef.assetManager->LoadTexture("platformer_tileset.png", "media");
	AppRef.assetManager->LoadTexture("catFighter.png", "media");
	AppRef.assetManager->LoadTexture("TilemapDebug.png", "media");

	////Construct Tilesets//
	tileset = new Tileset(32, 32, AppRef.assetManager->GetTexture("platformer_tileset"));
	debug_tileset = new Tileset(32, 32, AppRef.assetManager->GetTexture("TilemapDebug"));

	////Initialize Entities//
	cat = new CatEntity(64, 64, 1, 1, 0, 0, 10, 11, 12);
	cat->GetComponent<SpriteRenderer>()
		->SetSprite(*AppRef.assetManager->TextureToSprite("catFighter", 64, 64));

	//Construct Map//
	world = new Map(32, 23, 32, 32);
	
	//Load Tile Maps//
	world->LoadLayer("media/cf_map_Backdrop.csv");
	world->LoadLayer("media/cf_map_Background.csv");
	world->LoadLayer("media/cf_map_Foreground.csv");
	world->LoadLayer("media/cf_map_Foreground2.csv");
	
	//Load Collision Map//
	world->LoadCollisionMap("media/cf_map_CollisionLayer.csv");
	
	//Load Tilesets//
	world->SetTileset(tileset);
	world->LoadDebugTileset(debug_tileset);
	world->GetCollisionLayer()->AddEntities(cat);

	sprite = new sf::Sprite(*AppRef.assetManager->GetTexture("TilemapDebug"));
	sprite->setColor(sf::Color::Red);
	sprite->setTextureRect(sf::IntRect(0, 0, 32, 32));

	_player = new Player(*AppRef.inputHandler);
	_player->SetEntity(cat);
}


ArenaState::~ArenaState()
{
}

void ArenaState::Update(float dt)
{
	if (AppRef.inputHandler->IsKeyPressed(sf::Keyboard::Key::P))
	{
		if (AppRef.Paused())
			AppRef.Pause(false);
		else
			AppRef.Pause(true);
	}

	if (AppRef.Paused()) return;



	world->Update(dt);
	_player->Update(dt);

//	cat->Update(dt);
}

void ArenaState::Draw(sf::RenderWindow * renderWindow)
{
	renderWindow->clear(sf::Color::Black);

	world->Draw(renderWindow);
	_player->Draw(renderWindow);
	//cat->Draw(renderWindow);

	renderWindow->display();
}
