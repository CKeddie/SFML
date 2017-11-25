#include "Player.h"

Player::Player()
	: ISubject<sf::Packet>()
{

}

Player::Player(std::string name, int id)
	: Player()
{
	_name = name;
	_player_id = id;
}

Player::~Player()
{
	if (_entity)
	{
		delete _entity;
		_entity = nullptr;
	}

	if (_sprite_renderer)
	{
		delete _sprite_renderer;
		_sprite_renderer = nullptr;
	}

	if (_body)
	{
		delete _body;
		_body = nullptr;
	}
}

void Player::Update(float dt)
{
	if (!_entity)return;

	//Sprite Flipping
	if (_body->GetVelocity().x > 0)
	{
		_sprite_renderer->SetDirection(Right);
	}
	else if (_body->GetVelocity().x < 0)
	{
 		_sprite_renderer->SetDirection(Left);
	}

	//Run & Idle animations
	if (_body->IsGrounded())
	{
		if (std::abs(_body->GetVelocity().x) > 0.1f)
		{
			_animator->SetAnimationState(Run);
		}
		else
		{
			_animator->SetAnimationState(Idle);
		}
	}
	else
	{
		//Jump Animation
		if (_body->GetVelocity().y > 0)
		{
			_animator->SetAnimationState(Jump);
		}
		//Fall Animation
		else if (_body->GetVelocity().y < 0)
		{
			_animator->SetAnimationState(Fall);
		}
	}

	_entity->Update(dt);
}

void Player::Draw(sf::RenderWindow * renderWindow)
{
	if (!_entity)return;

	_entity->Draw(renderWindow);
}

void Player::CreateEntity(sf::Sprite * sprite, Map & map, sf::Vector2f spawn)
{	
	_spawn_point = spawn;
	_entity = new CatEntity(spawn, sf::Vector2f(1, 1), 0, sf::Vector2f(0, 10), sf::Vector2f(8, 12));

	_sprite_renderer = _entity->GetComponent<SpriteRenderer>();
	_body = _entity->GetComponent<PhysicsBody>();
	_animator = _entity->GetComponent<CatAnimator>();
	_sprite_renderer->SetSprite(*sprite);

	_entity->SetPosition(_spawn_point);

	map.GetCollisionLayer()->AddEntities(_entity);
}

Entity * Player::GetEntity()
{
	return _entity;
}

void Player::ResetEntity()
{
	if (!_entity) return;

	_entity->SetPosition(_spawn_point);
	//add health
}