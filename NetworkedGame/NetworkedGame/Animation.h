#pragma once

#include "SFML\Graphics.hpp"
#include <vector>

class Animation
{
public:
	Animation(const char *, int *, int, sf::Texture*, sf::IntRect);
	~Animation();
	void Update(float);
	void Reset();
	std::string getName();
	sf::IntRect getCurrentFrame();\
private:
	std::string _name;
	std::vector<sf::IntRect> _frames;
	int _currentFrame = 0;
	int _iter = 0;
	int* _sequence;
	int _numFrames;
	float _frameTimer = 0;
	float _frameLength = 0.1f;
};

