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

void GridElement::SetMargin(int left, int right, int top, int bottom) {
	marginLeft = left;
	marginRight = right;
	marginTop = top;
	marginBottom = bottom;
}

void GridElement::SetMargin(int size) {
	SetMargin(size, size, size, size);
}

GridElement::~GridElement()
{
}

