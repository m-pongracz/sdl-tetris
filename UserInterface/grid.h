#ifndef GRID_H
#define GRID_H

#include <vector>;
#include "row.h";
#include "point.h";
class Grid
{
public:
	Grid(int width, int height);
	~Grid();
	auto width() const& -> const int& { return _width; };
	auto width() & -> const int& { return _width; };
	auto height() const& -> const int& { return _height; };
	auto height() & -> const int& { return _height; };
	auto rows() const& -> const std::vector<Row*>& { return _rows; };
	auto rows() & -> const std::vector<Row*>& { return _rows; };
	void AddRow(Row* row);
	Point GetColumnPosition(int row, int column);
	Point GetRowPosition(int row);
	const Column* GetColumnAt(int row, int column);
	void RecalculateGrid();
private:
	int _width;
	int _height;
	std::vector<Row*> _rows;
	//int getAlignMargin(Column* column);
};

#endif