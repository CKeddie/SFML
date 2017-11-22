#include "Animator.h"
#include "Entity.h"
#include "SpriteRenderer.h"
Animator::Animator(Entity & entity)
	: Component(entity)
	
{

}

Animator::~Animator()
{
}
void Animator::Update(float deltaTime)
{
	if (!_current_anim) return;

	_current_anim->Update(deltaTime);
}

void Animator::Draw(sf::RenderWindow * window)
{
	if(_entity.GetComponent<SpriteRenderer>() && _current_anim)
		_entity.GetComponent<SpriteRenderer>()->SetSpriteRect(_current_anim->getCurrentFrame());
}

void Animator::SetAnimationState(int id)
{
	if (!_animations[id])
	{
		std::cout << "Animation id: " << id << " does not exist." << std::endl;
		return;
	}

	if (_current_anim)
	{
		if (_current_anim != _animations[id])
		{
			_current_anim->Reset();
			_current_anim = _animations[id];
		}
	}
	else
		_current_anim = _animations[id];
}

int Animator::GetCurrentState()
{
	return _current_animation;
}

void Animator::AddAnimation(int id, Animation * animation)
{
	_animations[id] = animation;
}

void Animator::RemoveAnimation(int id)
{
	_animations.erase(id);
}
