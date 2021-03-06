#pragma once
#include "SFML\Graphics.hpp"
#include <memory>
#include <iostream>
#include <typeinfo>
#include <unordered_map>

using namespace std;

//class IData
//{
//
//};

//class IEntityData
//	: IData
//{
//public:
//	IEntityData(Entity & entity);
//	virtual sf::Vector2f Position() = 0;
//protected:
//	Entity & _entity;
//};


class Component;

class Entity
	//: IEntityData
{
public:
	Entity();
	Entity(sf::Vector2f, sf::Vector2f, float);
	Entity(float, float, float, float, float);
	virtual ~Entity();

	virtual void Update(float);
	virtual void Draw(sf::RenderWindow*);

	void AddComponent(Component* c);
	template <typename T> T* GetComponent();
	
	//Transform
	sf::Vector2f Position() { return *_position; }
	void SetPosition(sf::Vector2f pos) 
	{
		_position = new sf::Vector2f(pos);
	}	
	void SetPosition(float x, float y) 
	{
		_position = new sf::Vector2f(x, y);
	}
	


	virtual void Translate(sf::Vector2f amount) { _position->x += amount.x; _position->y += amount.y; }

protected:
	float*			 _rotation;
	sf::Vector2f*	 _position;
	sf::Vector2f*	 _scale;

	unordered_map<const type_info *, Component *> _components;
};

template<typename T>
inline T * Entity::GetComponent()
{
	if (_components.count(&typeid(T)) != 0)
	{
		return static_cast<T*>(_components[&typeid(T)]);
	}
	else
	{
		return nullptr;
	}
}
