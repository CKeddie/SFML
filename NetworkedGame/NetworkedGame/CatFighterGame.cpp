#include "SFML\System\Vector2.hpp"

#include "CatFighterGame.h"


CatFighterGame::CatFighterGame(std::string title, int width, int height, int offX, int offY)
	: Application::Application(title, width, height, offX, offY)
{
	//Load Textures//
	_assetManager->LoadTexture("platformer_tileset.png", "media");
	_assetManager->LoadTexture("catFighter.png", "media");
	_assetManager->LoadTexture("TilemapDebug.png", "media");

	//Construct Tilesets//
	tileset = new Tileset(32, 32, _assetManager->GetTexture("platformer_tileset"));
	debug_tileset = new Tileset(32, 32, _assetManager->GetTexture("TilemapDebug"));

	//Initialize Entities//
	cat = new CatEntity(0, 0, 1, 1, 0, 0, 10, 11, 12);
	cat->GetComponent<SpriteRenderer>()
		->SetSprite(*_assetManager->TextureToSprite("catFighter", 64, 64));

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

	sprite = new sf::Sprite(*_assetManager->GetTexture("TilemapDebug"));
	sprite->setColor(sf::Color::Red);
	sprite->setTextureRect(sf::IntRect(0, 0, 32, 32));
}


CatFighterGame::~CatFighterGame()
{
	Application::~Application();
}

template <typename T> int sgn(T val) {
	return (T(0) < val) - (val < T(0));

}

void CatFighterGame::Update()
{
		

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		int x = sf::Mouse::getPosition().x;
		int y = sf::Mouse::getPosition().y;
		//cat->SetPosition(sf::Vector2f(x, y));
	}

	if ( _inputHandler->IsKeyDown(sf::Keyboard::Key::A))
		cat->GetComponent<PhysicsBody>()->SetTargetSpeedX(-100);

	else if (_inputHandler->IsKeyDown(sf::Keyboard::Key::D))
		cat->GetComponent<PhysicsBody>()->SetTargetSpeedX(100);
	else
		cat->GetComponent<PhysicsBody>()->SetTargetSpeedX(0);

	if (_inputHandler->IsKeyPressed(sf::Keyboard::Key::Space))
 		cat->GetComponent<PhysicsBody>()->SetTargetSpeedY(-10 * 32);
		
	if (_inputHandler->IsKeyPressed(sf::Keyboard::Key::R))
	{
		cat->SetPosition(sf::Vector2f(0, 0));

		cat->GetComponent<PhysicsBody>()->GetVelocity()->x = 0;
		cat->GetComponent<PhysicsBody>()->GetVelocity()->y = 0;
	}

	cat->Update(_timer->getTime());
	world->Update(_timer->getTime());
	Application::Update();
	

}

float IntervalDistance(float minA, float maxA, float minB, float maxB)
{
	if (minA < minB)
	{
		return minB - maxA;
	}
	else {
		return minA - maxB;
	}
}

void CatFighterGame::CleanUp()
{
	delete _renderWindow;
	_renderWindow = nullptr;

	delete cat;
	cat = nullptr;
/*
	delete cat2;
	cat2 = nullptr;
*/
	delete _timer;
	_timer = nullptr;
	
	delete _assetManager;
	_assetManager = nullptr;
}


void CatFighterGame::Draw()
{
	Application::Draw();
	_renderWindow->clear(sf::Color::Black);
	world->Draw(_renderWindow);
	//cat2->Draw(_renderWindow);

	//TODO: Make input handler static
	//if (_inputHandler->IsKeyDown(sf::Keyboard::Key::F1))
	/*{
		int idx = (int)cat->Position().x / 32;
		int idy = (int)cat->Position().y / 32;

		int x, y, w, h;*/

		//sf::FloatRect f = cat->GetComponent<>()->getGlobalBounds();

		/*sprite->setColor(sf::Color::Green);
		sprite->setTextureRect(sf::IntRect(0, 0, f.width, f.height));
		sprite->setPosition(sf::Vector2f(
			cat->Position().x - f.width / 2,
			cat->Position().y - f.height / 2));*/
		//_renderWindow->draw(*sprite);
		//cat->GetCollider().DebugDraw(_renderWindow, sprite);
	//}
	cat->Draw(_renderWindow);

	_renderWindow->display();
}
