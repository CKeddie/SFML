#include "GameStateManager.h"

#include "GameState.h"

GameStateManager::GameStateManager()
{

}

GameStateManager::~GameStateManager()
{
	_game_states.empty();
}

void GameStateManager::Update(float dt)
{
	_game_states.top()->Update(dt);
}

void GameStateManager::Draw(sf::RenderWindow * renderWindow)
{
	_game_states.top()->Draw(renderWindow);
}

void GameStateManager::PushState(GameState * state)
{
	_game_states.push(state);
}

void GameStateManager::PopState()
{
	_game_states.pop();
}

void GameStateManager::ChangeState(GameState * state)
{
	while (_game_states.size() > 0)
	{
		_game_states.pop();
	}
	PushState(state);
}
