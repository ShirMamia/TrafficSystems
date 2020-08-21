#pragma once
#include <iostream>
#include "street.h"
#include "Car.h"
class Cell
{
private:
	bool _isJunction;
	const Street* _horizontalSt;
	const Street* _verticalSt;
	int _horizontalCellNumber;
	int _verticalCellNumber;
	Car* _horizontalCar;
	Car* _verticalCar;

public:
	Cell(bool isJunction = false,Street* horizontalSt = nullptr, Street* verticalSt = nullptr, int horizontalCellNumber = 0,
		int verticalCellNumber = 0, Car* horizontalCar = nullptr , Car* verticalCar = nullptr):
		_isJunction(isJunction), _horizontalSt(horizontalSt), _verticalSt(verticalSt), _horizontalCellNumber(horizontalCellNumber),
		_verticalCellNumber(verticalCellNumber), _horizontalCar(horizontalCar),_verticalCar(verticalCar){}

	bool getIsJunction(){ return _isJunction; }
	void setIsJunction(bool isJunction) {_isJunction = isJunction;}

	const Street* getHorizontalSt() const { return _horizontalSt; }
	const Street* getVerticalSt() const { return _verticalSt; }

	int getHorizontalCellNumber() const { return _horizontalCellNumber; }
	int getVerticalCellNumber() const { return _verticalCellNumber; }

	Car* getHorizontalCar() const { return _horizontalCar; }
	Car* getVerticalCar() const { return _verticalCar; }


	void setHorizontalSt(const Street* st) { _horizontalSt = st;}
	void setHorizontalCellNumber(const int numberOfCell) { _horizontalCellNumber = numberOfCell; }
	void setHorizontalCar(Car* car) { _horizontalCar = car; }
	void setHorizontal(const Street* st, const int numberOfCell);

	void setVerticalSt(const Street* st) { _verticalSt = st; }
	void setVerticalCellNumber(const int numberOfCell) { _verticalCellNumber = numberOfCell; }
	void setVerticalCar(Car* car) { _verticalCar = car; }
	void setVertical(const Street* st, const int numberOfCell);


};

