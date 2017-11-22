#pragma once

#include "SFML\Graphics.hpp"
#include "SFML\Network.hpp"

class Entity;
class InputHandler;

class Player 
{
public:
	Player(InputHandler & inputHandler);
	~Player();

	void Update(float);
	void Draw(sf::RenderWindow*);

	void SetEntity(Entity * entity);
	Entity * GetEntity();

private:
	int _player_index = 0;
	sf::Vector2f * _spawn_point;
	InputHandler & _input_handler;
	Entity * _player_entity;
	int _max_charges = 2;
	int _jump_charges = _max_charges;
};