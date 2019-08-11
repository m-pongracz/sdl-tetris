#ifndef COLUMN_H
#define COLUMN_H

#include "grid_element.h";

class Column : 
	public GridElement
{
public:
	Column() : GridElement() {

	}

	Column(int w, int h) : GridElement(w, h) {

	}

	void SetRowPosition(int rowPosition);

	auto rowPosition() const& -> const int& { return _rowPosition; };
	auto rowPosition() & -> const int& { return _rowPosition; };
private:
	int _rowPosition;
};

#endif