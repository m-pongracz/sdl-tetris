#ifndef GRIDELEMENT_H
#define GRIDELEMENT_H

#include "dimensions.h"

enum AlignH { aLeft, aRight, aMiddle };
enum AlignV { aTop, aBottom, aCenter };


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
	void SetMargin(int left, int right, int top, int bottom);
	void SetMargin(int size);

	auto order() const& -> const int& { return _order; };
	auto order() & -> const int& { return _order; };
	auto position() const& -> const int& { return _position; };
	auto position() & -> const int& { return _position; };
	auto dimensions() const& -> const Dimensions& { return _dimensions; };
	auto dimensions() & -> const Dimensions& { return _dimensions; };

	int marginLeft = 0;
	int marginRight = 0;
	int marginTop = 0;
	int marginBottom = 0;
	//Align align;

};

#endif