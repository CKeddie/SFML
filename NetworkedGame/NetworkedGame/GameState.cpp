#include "GameState.h"
#include "GUILabel.h"
#include "Application.h"

GameState::GameState(Application & app)
	: AppRef(app)
{

	AppRef.assetManager->LoadFont("tahoma.ttf");

	_control_manager = new GUIControlManager(*AppRef.inputHandler);	
}


GameState::~GameState()
{
	if (_control_manager)
	{
		delete _control_manager;
		_control_manager = nullptr;
	}
}

void GameState::Update(float deltaTime)
{
	_control_manager->Update(deltaTime);
}

void GameState::Draw(sf::RenderWindow * renderWindow)
{
	renderWindow->clear(sf::Color::Black);
	_control_manager->Draw(renderWindow);
}
