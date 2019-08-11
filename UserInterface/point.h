#ifndef POINT_H
#define POINT_H

#include <vector>
#include "row.h"
class Point
{
public:
	Point(int x, int y);

	auto x() const& -> const int& { return _x; };
	auto x() & -> const int& { return _x; };
	auto y() const& -> const int& { return _y; };
	auto y() & -> const int& { return _y; };

	~Point();
private:
	int _x;
	int _y;
};

#endif