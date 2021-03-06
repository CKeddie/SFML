#pragma once

#include "SFML\Graphics.hpp"
#include "SFML\Network.hpp"
#include "ISubject.h"
#include "Player.h"

class Entity;
class InputHandler;

class LocalPlayer
	: public Player
	, public ISubject<sf::Packet>
{
public:
	LocalPlayer(std::string name, int id, InputHandler & inputHandler);
	~LocalPlayer();

	void Update(float) override;
	void Draw(sf::RenderWindow*) override;
private:
	InputHandler & _input_handler;
	float _packet_timer = 0.0f;
	int _jump_charges = 0;
	int _max_jump_charges = 2;
	float _run_speed = 100.0f;
	float _jump_force = 300.0f;
};