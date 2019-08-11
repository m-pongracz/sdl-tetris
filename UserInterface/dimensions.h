#ifndef DIMENSIONS_H
#define DIMENSIONS_H

#include <vector>

class Dimensions
{
public:
	Dimensions(int w, int h);

	void SetWidth(int width);
	void SetHeight(int height);

	auto w() const& -> const int& { return _w; };
	auto w() & -> const int& { return _w; };
	auto h() const& -> const int& { return _h; };
	auto h() & -> const int& { return _h; };

	~Dimensions();
private:
	int _w;
	int _h;
};

#endif