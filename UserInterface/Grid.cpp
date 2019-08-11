#include "Grid.h"



Grid::Grid(int width, int height)
{
	_width = width;
	_height = height;
}


Grid::~Grid()
{
}

void Grid::AddRow(Row* row)
{
	row->SetOrder(_rows.size());
	row->SetPosition(_rows.size());

	_rows.push_back(row);
	//RecalculateGrid();
}

void Grid::RecalculateGrid()
{
	int dynamicRows = 0;
	int staticWidth = 0;
	for (auto r : _rows) {
		if (r->dimensions().h() == 0) {
			++dynamicRows;
		}
		else {
			staticWidth += r->dimensions().h();
		}
	}

	for (auto r : _rows) {
		if (r->dimensions().h() == 0) {
			r->SetHeight((_height - staticWidth) / (_rows.size() - dynamicRows));
		}
		if (r->dimensions().w() == 0) {
			r->SetWidth(_width);
		}
		for (auto c : r->columns()) {

			if (c->dimensions().h() == 0) {
				c->SetHeight(r->dimensions().h());
			}
			if (c->dimensions().w() == 0) {
				c->SetWidth(r->dimensions().w() / r->columns().size());
			}
		}
	}
}

Point Grid::GetColumnPosition(int row, int column) {
	int x = 0;
	int y = GetRowPosition(row);
	int totalColumnWidth = 0;

	Row* r = _rows[row];
	Column* c = r->columns()[column];

	for (int i = 0; i < r->columns().size(); ++i) {
		Column* ci = r->columns()[i];
		totalColumnWidth += ci->dimensions().w();
		if (column != 0 && i < column) {
			x += ci->dimensions().w();
		}
	}

	x += getAlignMargin(c);

	return Point(x, y);
}

int Grid::getAlignMargin(Column* column) {
	int totalColumnWidth = 0;

	Row* r = _rows[column->rowPosition()];
	Column* c = r->columns()[column->position()];

	for (int i = 0; i < r->columns().size(); ++i) {
		Column* ci = r->columns()[i];
		totalColumnWidth += ci->dimensions().w();
	}

	if (c->align == Align::center) {
		return ((r->dimensions().w() - totalColumnWidth) / 2) / r->columns().size();
	}
	else if (c->align == Align::right) {
		return ((r->dimensions().w() - totalColumnWidth) / r->columns().size());
	}
	else {
		return 0;
	}
}

int Grid::GetRowPosition(int row) {
	int y = 0;
	for (int i = 0; i < row; ++i) {
		y += _rows[i]->dimensions().h();
	}
	return y;
}

const Column* Grid::GetColumnAt(int row, int column) {
	return _rows[row]->columns()[column];
}

