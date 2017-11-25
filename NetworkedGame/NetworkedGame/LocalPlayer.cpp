#include "LocalPlayer.h"
#include "InputHandler.h"


LocalPlayer::LocalPlayer(std::string name, int id, InputHandler & inputHandler)
	: Player(name, id)
	, _input_handler(inputHandler)	
{

}

LocalPlayer::~LocalPlayer()
{
	Player::~Player();
}

void LocalPlayer::Update(float dt)
{
	Player::Update(dt);
	sf::Packet p;

	if (_body->IsGrounded())
		_jump_charges = _max_jump_charges;

	if (_entity)
	{
		if (_input_handler.IsKeyDown(sf::Keyboard::A))
		{
			_body->SetTargetSpeedX(-_run_speed);
		}
		else if (_input_handler.IsKeyDown(sf::Keyboard::D))
		{
			_body->SetTargetSpeedX(_run_speed);
		}
		else
		{
			_body->SetTargetSpeedX(0.0f);
		}

		if (_input_handler.IsKeyPressed(sf::Keyboard::R))
		{
			ResetEntity();
		}

		if (_jump_charges > 0)
		{
			if (_input_handler.IsKeyPressed(sf::Keyboard::Space))
			{
				_body->Impulse(-_jump_force);
				--_jump_charges;
			}
		}

		sf::Packet p;
		p << _player_id;
		p << _body->GetVelocity().x;
		p << _body->GetVelocity().y;		
		Notify(p);
	}
}

void LocalPlayer::Draw(sf::RenderWindow * renderWindow)
{
	Player::Draw(renderWindow);
}