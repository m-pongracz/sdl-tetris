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
	int staticRows = 0;
	int staticRowWidth = 0;
	for (auto r : _rows) {
		if (r->dimensions().h() != 0) {
			++staticRows;
			staticRowWidth += r->dimensions().h() + r->marginTop + r->marginBottom;
		}
	}

	for (auto r : _rows) {
		if (r->dimensions().h() == 0) {
			r->SetHeight(((_height - staticRowWidth) / (_rows.size() - staticRows)) - (r->marginTop + r->marginBottom));
		}
		if (r->dimensions().w() == 0) {
			r->SetWidth(_width - (r->marginLeft + r->marginRight));
		}

		int staticColumnWidth = 0;
		int staticColumns = 0;

		for (auto c : r->columns()) {
			if (c->dimensions().w() != 0) {
				++staticColumns;
				staticColumnWidth += c->dimensions().w() + c->marginLeft + c->marginRight;
			}
		}

		for (auto c : r->columns()) {

			if (c->dimensions().h() == 0) {
				c->SetHeight(r->dimensions().h() - (c->marginTop + c->marginBottom));
			}
			if (c->dimensions().w() == 0) {
				c->SetWidth(
					(
					(r->dimensions().w() - staticColumnWidth) / (r->columns().size() - staticColumns)
						)
					-
					(c->marginLeft + c->marginRight)
				);
			}
		}
	}
}

Point Grid::GetColumnPosition(int row, int column) {
	int x = 0;
	int y = GetRowPosition(row).y();
	int totalColumnWidth = 0;

	Row* r = _rows[row];

	x += r->marginLeft;

	Column* c = r->columns()[column];

	y += c->marginTop;

	for (int i = 0; i < r->columns().size(); ++i) {
		Column* ci = r->columns()[i];
		totalColumnWidth += ci->dimensions().w();
		if (column != 0 && i < column) {
			x += ci->dimensions().w() + ci->marginLeft;
		}
	}

	x += c->marginLeft;

	//x += getAlignMargin(c);

	return Point(x, y);
}

//int Grid::getAlignMargin(Column* column) {
//	int totalColumnWidth = 0;
//
//	Row* r = _rows[column->rowPosition()];
//	Column* c = r->columns()[column->position()];
//
//	for (int i = 0; i < r->columns().size(); ++i) {
//		Column* ci = r->columns()[i];
//		totalColumnWidth += ci->dimensions().w();
//	}
//
//	if (c->align == Align::center) {
//		return ((r->dimensions().w() - totalColumnWidth) / 2) / r->columns().size();
//	}
//	else if (c->align == Align::right) {
//		return ((r->dimensions().w() - totalColumnWidth) / r->columns().size());
//	}
//	else {
//		return 0;
//	}
//}

Point Grid::GetRowPosition(int row) {

	int y = 0;
	for (int i = 0; i < row; ++i) {
		auto r = _rows[i];
		y += r->dimensions().h() + r->marginTop + r->marginBottom;
	}
	auto r = _rows[row];

	y += r->marginTop;
	int x = r->marginLeft;

	return Point(x, y);
}

const Column* Grid::GetColumnAt(int row, int column) {
	return _rows[row]->columns()[column];
}

