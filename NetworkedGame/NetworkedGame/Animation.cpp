#include "Animation.h"



Animation::Animation(const char* name, int* frames, int numFrames, sf::Texture* txr, sf::IntRect rect)
{
	_name = name;

	_sequence = new int[numFrames];
	for(int i = 0; i < numFrames; i++)
		_sequence[i] = frames[i];

	_numFrames = numFrames;

	int numX = txr->getSize().x / rect.width;
	int numY = txr->getSize().y / rect.height;

	for (int y = 0; y < numY; y++)
	{
		for (int x = 0; x < numX; x++)
		{
			_frames.push_back(sf::IntRect(x * rect.width, y * rect.height, rect.width, rect.height));
		}
	}

	_currentFrame = _sequence[0];
}

Animation::~Animation()
{
}

void Animation::Update(float deltaTime)
{
	_frameTimer += deltaTime;
	if(_frameTimer >= _frameLength)
	{ 
		_frameTimer = 0;
		_iter++;
		if (_iter >= _numFrames)
			Reset();
		else 
			_currentFrame = _sequence[_iter];		
	}
}

void Animation::Reset()
{
	_iter = 0;
	_frameTimer = 0;
	_currentFrame = _sequence[_iter];
}

std::string Animation::getName()
{
	return _name;
}

sf::IntRect Animation::getCurrentFrame()
{
	return _frames.at(_currentFrame);
}
