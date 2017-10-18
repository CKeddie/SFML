#include "ILayer.h"

IntLayer::IntLayer(int w, int h)
{
	_width = new int (w);
	_height = new int(h);

	_indices = new int[w * h];
}

IntLayer::~IntLayer()
{
	delete _width;
	_width = nullptr;
	delete _height;
	_height = nullptr;
	delete _indices;
	_indices = nullptr;
}

int* IntLayer::LoadLayer(std::string filename)
{
	std::ifstream file(filename, std::ifstream::in);

	std::string index;
	int i = 0;
	while (file.good() && i < *_width * *_height)
	{
		char c = file.get();

		if (c != ',' && c != '\n')
			index += c;
		else if (c == ',' || c == '\n')
		{
			if (index == "-1")
				_indices[i] = 0;
			else
			{
				std::stringstream ss(index);
				int val = 0;
				ss >> val;
				_indices[i] = val;
			}

			index = "";
			i++;
		}
	}

	file.close();

	return _indices;
}

int* IntLayer::GetIndices()
{
	return _indices;
}

int IntLayer::GetIndex(int i)
{
	return _indices[i];
}

int IntLayer::GetIndex(int x, int y)
{
	if (x >= 0 && x < *_width && y >= 0 && y < *_width)
		return _indices[x + y * *_width];
	else
		return 0;

}
