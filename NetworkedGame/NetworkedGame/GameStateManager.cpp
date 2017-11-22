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
	if(_game_states.size() > 0)
		_game_states.top()->Update(dt);
}

void GameStateManager::Draw(sf::RenderWindow * renderWindow)
{
	if (_game_states.size() > 0)
		_game_states.top()->Draw(renderWindow);
}

void GameStateManager::PushState(GameState * state)
{
	_game_states.push(state);
}

void GameStateManager::PushState(std::string state)
{
	_game_states.push(_gamestate_repository[state]);
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
void GameStateManager::ChangeState(std::string state)
{
	while (_game_states.size() > 0)
	{
		_game_states.pop();
	}
	PushState(state);
}

void GameStateManager::AddState(std::string id, GameState * state)
{
	_gamestate_repository[id] = state;
}

void GameStateManager::RemoveState(std::string id)
{
	_gamestate_repository.erase(id);
}

void GameStateManager::OnNotify(std::pair<int, std::string> command)
{
	switch (command.first)
	{
	case 0:
		break;
	case 1:
		PushState(_gamestate_repository[command.second]);
		break;
	case 2:
		PopState();
	case 3:
		ChangeState(_gamestate_repository[command.second]);
	}
}
