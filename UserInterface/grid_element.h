#ifndef GRIDELEMENT_H
#define GRIDELEMENT_H

#include "dimensions.h"

enum Align { left, right, center };

class GridElement
{
protected:
	Dimensions _dimensions = Dimensions(0, 0);
	int _order;
	int _position;
public:
	GridElement();
	~GridElement();
	GridElement(int width, int height);
	
	void SetWidth(int width);
	void SetHeight(int height);
	void SetOrder(int order);
	void SetPosition(int position);

	auto order() const& -> const int& { return _order; };
	auto order() & -> const int& { return _order; };
	auto position() const& -> const int& { return _position; };
	auto position() & -> const int& { return _position; };
	auto dimensions() const& -> const Dimensions& { return _dimensions; };
	auto dimensions() & -> const Dimensions& { return _dimensions; };

	Align align;
};

#endif