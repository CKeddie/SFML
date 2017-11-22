#pragma once
#include "Component.h"

class PhysicsBody :
	public Component
{
public:
	PhysicsBody(Entity & entity);
	void Update(float) override;
	void Draw(sf::RenderWindow*) override;
	void SetPosition(sf::Vector2f);
	sf::Vector2f* GetVelocity();
	void SetPushForce(sf::Vector2f);
	void SetTargetSpeedX(float f);
	void SetTargetSpeedY(float f);

	void Impulse(float force);
	void SetGrounded(bool);
	bool IsGrounded();
	void SetWalled(bool);
	bool IsWalled();
	~PhysicsBody();
protected:
	bool is_grounded = false;
	bool is_walled = false;
	float _x_acceleration = .5f;
	float _y_acceleration = .5f;
	float _gravity = 19.81f;
	float _gravity_scale = 16.0f;
	sf::Vector2f* _velocity;
	sf::Vector2f* _target_speed;
	sf::Vector2f* _push_force;
	sf::Vector2f* x_direction;
};

