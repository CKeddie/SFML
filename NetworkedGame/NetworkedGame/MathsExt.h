#pragma once

#include "SFML\Graphics.hpp"

namespace me
{

	//float Dot(float ax, float ay, float bx, float by)
	//{
	//	return ax * bx + ay * by;
	//}

	float Dot(sf::Vector2f a, sf::Vector2f b)
	{
		return a.x * b.x + a.y * b.y;
	}

	template <typename T> int sgn(T val) {
		return (T(0) < val) - (val < T(0));

	}
}