#include "CatAnimator.h"


CatAnimator::CatAnimator(Entity & entity)
	: Animator(entity)
{

}

CatAnimator::~CatAnimator()
{
	Animator::~Animator();
}

void CatAnimator::Update(float dt)
{
	Animator::Update(dt);
}

void CatAnimator::Draw(sf::RenderWindow * window)
{
	Animator::Draw(window);
}
