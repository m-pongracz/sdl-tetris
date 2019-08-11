#include "grid_element.h"

GridElement::GridElement()
{
	_dimensions = Dimensions(0, 0);
}

GridElement::GridElement(int width, int height)
{
	_dimensions = Dimensions(width, height);
}

void GridElement::SetWidth(int width) {
	_dimensions.SetWidth(width);
}

void GridElement::SetHeight(int height) {
	_dimensions.SetHeight(height);
}

void GridElement::SetOrder(int order) {
	_order = order;
}

void GridElement::SetPosition(int position) {
	_position = position;
}

GridElement::~GridElement()
{
}
