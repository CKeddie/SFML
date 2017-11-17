#pragma once

#include "SFML\Graphics.hpp"
#include <vector>

class Animation
{
public:
	Animation(int* sequence, int numFrames, int txrWidth, int txrHeight, int fwidth, int fheight);
	~Animation();
	void Update(float);
	void Reset();
	sf::IntRect getCurrentFrame();
private:
	std::vector<sf::IntRect> _frames;
	int _currentFrame = 0;
	int _iter = 0;
	int* _sequence;
	int _numFrames;
	float _frameTimer = 0;
	float _frameLength = 1;
};

