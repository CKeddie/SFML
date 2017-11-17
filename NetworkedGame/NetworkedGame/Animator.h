#pragma once
//#include "BaseStateMachine.h"
#include "Animation.h"
#include "Component.h"
#include <map>
#include "AnimationState.h"
class Entity;

class Animator 
	: public Component
{
public:
	Animator(Entity & entity);
	~Animator();
	virtual void Update(float) = 0;
	virtual void Draw(sf::RenderWindow* window);
	void SetAnimationState(int id);
	virtual int  GetCurrentState();
	void AddAnimation(int id, Animation * animation);
	void RemoveAnimation(int id);
	
protected:
	std::map<int,Animation*> _animations;
	Animation * _current_anim;
	int _current_animation = 0;
};

