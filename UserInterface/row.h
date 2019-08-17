#ifndef ROW_H
#define ROW_H

#include <vector>;
#include "grid_element.h"
#include "column.h"

class Row :
	public GridElement
{
public:
	Row() : GridElement() {

	}
	Row(int w, int h) : GridElement(w, h) {

	}
	void AddColumn(Column* column);

	auto columns() const& -> const std::vector<Column*>& { return _columns; };
	auto columns() & -> const std::vector<Column*>& { return _columns; };
protected:
	std::vector<Column*> _columns;
};

#endif