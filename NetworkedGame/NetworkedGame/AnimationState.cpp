#include "AnimationState.h"

AnimationState::AnimationState(Animation * animation)
{
	_animation = animation;
}

AnimationState::~AnimationState()
{
	if (_animation)
	{
		delete _animation;
		_animation = nullptr;
	}
}

Animation * AnimationState::GetAnimation()
{
	return _animation;
}

void AnimationState::AddTransition(Transition transition)
{
	_transitions.push_back(transition);
}

void AnimationState::RemoveTransition(int id)
{
	_transitions.erase(_transitions.begin() + id);
}

std::vector<AnimationState::Transition> AnimationState::GetTransitions()
{
	return _transitions;
}
