#pragma once

#include <vector>
#include "Animation.h"

class AnimationState
{
protected:
	struct Transition
	{
		Animation _from;
		Animation _to;
		bool _condition;
	};

public:
	AnimationState(Animation * animation);
	~AnimationState();
	Animation * GetAnimation();
	void AddTransition(Transition);
	void RemoveTransition(int id);
	std::vector<Transition> GetTransitions();
private:
	Animation * _animation;
	std::vector<Transition> _transitions;

};
