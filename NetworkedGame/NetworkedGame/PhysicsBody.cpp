#include "PhysicsBody.h"
#include "Entity.h"

float Lerp(float a, float b, float t)
{
	return a + t * (b - a);
}

PhysicsBody::PhysicsBody(Entity& entity) 
	: Component(entity)
{
	_velocity = new sf::Vector2f(0, 0);
	_target_speed = new sf::Vector2f(0, 0);
	_push_force = new sf::Vector2f(0, 0);
}

PhysicsBody::~PhysicsBody()
{
	delete _velocity;
	_velocity = nullptr;

	delete _target_speed;
	_target_speed = nullptr;

	delete _push_force;
	_push_force = nullptr;
}


sf::Vector2f normalize(const sf::Vector2f& source)
{
	float length = sqrt((source.x * source.x) + (source.y * source.y));
	if (length != 0)
		return sf::Vector2f(source.x / length, source.y / length);
	else
		return source;
}


void PhysicsBody::Update(float deltaTime)
{	
	_velocity = _target_speed;

	_velocity->y += (_gravity * !is_grounded) * _gravity_scale * deltaTime;

	_entity.Translate(normalize(*_velocity) * deltaTime);
}

void PhysicsBody::Draw(sf::RenderWindow * window)
{
	//if (!_debug_mode)
	//	return;
	sf::VertexArray vel(sf::Lines, 2);
	vel[0].color = sf::Color::Red;
	vel[1].color = sf::Color::Red;
	float x = _entity.Position().x;
	float y = _entity.Position().y;
	float xv = x + _velocity->x;
	float yv = y + _velocity->y;
	vel[0].position = sf::Vector2f(x, y);
	vel[1].position = sf::Vector2f(xv, yv);
	window->draw(vel);
}

void PhysicsBody::SetPosition(sf::Vector2f pos)
{
	_entity.SetPosition(pos);
}

sf::Vector2f* PhysicsBody::GetVelocity()
{
	return _velocity;
}

void PhysicsBody::SetPushForce(sf::Vector2f push)
{
	_push_force->x = push.x;
	_push_force->y = push.y;
}

void PhysicsBody::SetTargetSpeedX(float f)
{
	_target_speed->x = f;
}

void PhysicsBody::SetTargetSpeedY(float f)
{
	_target_speed->y = f;
}

void PhysicsBody::Impulse(sf::Vector2f direction)
{
	_target_speed->x = direction.x;
	_target_speed->y = direction.y;
}

void PhysicsBody::SetGrounded(bool isGrounded)
{
	is_grounded = isGrounded;
}

bool PhysicsBody::IsGrounded()
{
	return is_grounded;
}

