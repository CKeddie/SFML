#include "Player.h"

#include "Entity.h"
#include "InputHandler.h"
#include "PhysicsBody.h"
#include "CatAnimator.h"
#include "SpriteRenderer.h"

enum Animations
{
	Idle,
	Run,
	Jump,
	Fall,
};

Player::Player(InputHandler & inputHandler)
	: _input_handler(inputHandler)
{
}

Player::~Player()
{
}

void Player::Update(float dt)
{
	if (_player_entity)
	{
		if (_input_handler.IsKeyDown(sf::Keyboard::A))
		{
			_player_entity->GetComponent<PhysicsBody>()->SetTargetSpeedX(-100.0f); 
			_player_entity->GetComponent<SpriteRenderer>()->SetDirection(-1);
		}
		else if (_input_handler.IsKeyDown(sf::Keyboard::D))
		{
			_player_entity->GetComponent<PhysicsBody>()->SetTargetSpeedX(100.0f);
			_player_entity->GetComponent<SpriteRenderer>()->SetDirection(1);
		}
		else
			_player_entity->GetComponent<PhysicsBody>()->SetTargetSpeedX(0.0f);
		
		if (_jump_charges > 0)
		{
			if (_input_handler.IsKeyPressed(sf::Keyboard::Space))
			{
				_player_entity->GetComponent<PhysicsBody>()->SetTargetSpeedY(-250.0f);
				--_jump_charges;
			}
		}
			
		if (_player_entity->GetComponent<PhysicsBody>()->IsGrounded())
			_jump_charges = _max_charges;

		if (_input_handler.IsKeyPressed(sf::Keyboard::R))
		{
			_player_entity->SetPosition(sf::Vector2f(64, 64));
		}

		if (_player_entity->GetComponent<PhysicsBody>()->IsGrounded())
		{
			if (_player_entity->GetComponent<PhysicsBody>()->GetVelocity()->x > 0)
				_player_entity->GetComponent<CatAnimator>()->SetAnimationState(Run);
			else if(_player_entity->GetComponent<PhysicsBody>()->GetVelocity()->x < 0)
				_player_entity->GetComponent<CatAnimator>()->SetAnimationState(Run);
			else
				_player_entity->GetComponent<CatAnimator>()->SetAnimationState(Idle);
		}
		else
		{
			if (_player_entity->GetComponent<PhysicsBody>()->GetVelocity()->y > 0)
				_player_entity->GetComponent<CatAnimator>()->SetAnimationState(Jump);
			else if (_player_entity->GetComponent<PhysicsBody>()->GetVelocity()->y < 0)
				_player_entity->GetComponent<CatAnimator>()->SetAnimationState(Fall);
		}

		_player_entity->Update(dt);
	}
}

void Player::Draw(sf::RenderWindow * renderWindow)
{
	if (_player_entity)
		_player_entity->Draw(renderWindow);
}


void Player::SetEntity(Entity * entity)
{
	_player_entity = entity;
}
Entity * Player::GetEntity()
{
	return _player_entity;
}
