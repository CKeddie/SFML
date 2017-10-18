#pragma once
//#include "BaseStateMachine.h"
#include "Animation.h"

class Entity;

class Animator //:	public BaseStateMachine<Animation>
{
public:
	Animator(Entity* entity);
	~Animator();
	//void Update(float) override;
	//void Draw(sf::RenderWindow* window) override;
};

