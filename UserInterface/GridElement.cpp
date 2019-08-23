#include "grid_element.h"

GridElement::GridElement()
{
}

GridElement::GridElement(int width = 0, int height = 0)
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

void GridElement::SetCoordiantes(int x, int y) {
	_coordinates.x = x;
	_coordinates.y = y;
}