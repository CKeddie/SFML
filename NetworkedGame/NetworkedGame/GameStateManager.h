#pragma once

#include "Application.h"
#include <stack>

class GameState;

class GameStateManager
{
public:
	GameStateManager();
	
	~GameStateManager();
	
	void Update(float);
	void Draw(sf::RenderWindow*);

	void PushState(GameState*);
	void PopState();
	void ChangeState(GameState*);

private:
	std::stack<GameState*> _game_states;
};

