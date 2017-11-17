#include "Animation.h"

Animation::Animation(int* sequence, int numFrames, int txrWidth, int txrHeight, int fwidth, int fheight)
{
	_numFrames = numFrames;

	int numX = txrWidth / fwidth;
	int numY = txrHeight / fheight;

	for (int i = 0; i < numFrames; ++i)
	{
		float row = (float)(sequence[i] % numX);
		float col = (float)(sequence[i] / numX * numY) / numY;
		
		_frames.push_back(sf::IntRect(row * fwidth, col * fheight, fwidth, fheight));
	}
	_frameTimer = 0.0f;
	_currentFrame = 0;
}

Animation::~Animation()
{

}

void Animation::Update(float deltaTime)
{
	_frameTimer += deltaTime;
	if(_frameTimer >= _numFrames)
	{ 
		_frameTimer = 0;
		_iter++;
		if (_iter > _numFrames)
			Reset();
		else  if(_iter < _numFrames)
			_currentFrame = _iter;		
	}
}

void Animation::Reset()
{
	_iter = 0;
	_frameTimer = 0;
	_currentFrame = 0;
}

sf::IntRect Animation::getCurrentFrame()
{
	return _frames.at(_currentFrame);
}
