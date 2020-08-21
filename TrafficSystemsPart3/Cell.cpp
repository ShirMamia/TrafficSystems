#include "Cell.h"

void Cell::setHorizontal(const Street* st, const int numberOfCell)
{
	setHorizontalSt(st);
	setHorizontalCellNumber(numberOfCell);
}

void Cell::setVertical(const Street* st, const int numberOfCell)
{
	setVerticalSt(st);
	setVerticalCellNumber(numberOfCell);
}
