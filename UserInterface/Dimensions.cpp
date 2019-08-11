#include "dimensions.h"

Dimensions::Dimensions(int w, int h)
{
	_w = w;
	_h = h;
}

void Dimensions::SetWidth(int width) {
	_w = width;
}

void Dimensions::SetHeight(int height) {
	_h = height;
}


Dimensions::~Dimensions()
{
}
