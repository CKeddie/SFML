#pragma once

#include <stack>
#include "SFML\Graphics.hpp"
#include "IObserver.h"

class GameState;

enum Commands{
	None,
	PushState,
	PopState,
	ChangeState,
};

class GameStateManager
	: public IObserver<std::pair<int, std::string>>
{
public:
	GameStateManager();
	
	~GameStateManager();
	
	void Update(float);
	void Draw(sf::RenderWindow*);

	void PushState(GameState*);
	void PushState(std::string state);
	void PopState();
	void ChangeState(GameState*);
	void ChangeState(std::string state);
	void AddState(std::string id, GameState* state);
	void RemoveState(std::string id);
	void OnNotify(std::pair<int, std::string>)override;

private:
	std::stack<GameState*> _game_states;
	std::map<std::string, GameState*> _gamestate_repository;
};

