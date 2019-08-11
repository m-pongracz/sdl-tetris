#include "Row.h"

void Row::AddColumn(Column* column) {
	column->SetOrder(_columns.size());
	column->SetPosition(_columns.size());
	column->SetRowPosition(_position);
	_columns.push_back(column);
}
