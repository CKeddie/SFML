#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

class IntLayer
{
public:
	IntLayer(int w, int h);
	~IntLayer();
	int* LoadLayer(std::string filename);
	int* GetIndices();
	int  GetIndex(int i);
	int  GetIndex(int x, int y);
protected:
	int _width;
	int _height;
	int* _indices;
};

