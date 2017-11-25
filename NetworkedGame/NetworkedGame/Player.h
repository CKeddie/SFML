#pragma once

#include "SFML\Graphics.hpp"
#include "SFML\Network.hpp"

#include "CatEntity.h"
#include "PhysicsBody.h"
#include "CatAnimator.h"
#include "SpriteRenderer.h"
#include "ISubject.h"
#include "Map.h"

class Player
	: public ISubject<sf::Packet>
{
protected:
	enum AnimationState
	{
		Idle,
		Run,
		Jump,
		Fall,
	};

	enum PlayerDirection
	{
		Left = -1,
		Right = 1,
	};

public:
	Player();
	Player(std::string name, int id);
	~Player();

	virtual void Update(float);
	virtual void Draw(sf::RenderWindow*);

	void CreateEntity(sf::Sprite * sprite, Map & map, sf::Vector2f spawn);

	int GetID() { return _player_id; }
	void SetID(int id) { _player_id = id; }

	std::string GetName() { return _name; }
	void SetName(std::string name) { _name = name; }
		
	Entity * GetEntity();
	
	void ResetEntity();
protected:
	std::string _name = "Default";
	int _player_id = 0;

	sf::Vector2f _spawn_point;
	Entity * _entity;
	PhysicsBody * _body;
	SpriteRenderer * _sprite_renderer;
	CatAnimator * _animator;
};

