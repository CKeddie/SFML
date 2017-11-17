#pragma once
#include "Animator.h"

class CatAnimator :
	public Animator
{
private:
	enum AnimState
	{
		Idle,
		Run,
		Jump,
		Fall,
		Attack,
	};
public:
	CatAnimator(Entity & entity);
	~CatAnimator();
	void Update(float) override;
	void Draw(sf::RenderWindow*) override;
	AnimState _current_state;
};

