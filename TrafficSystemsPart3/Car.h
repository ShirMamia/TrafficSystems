#pragma once
#include <iostream>
#include <map>
using namespace std;


class Car
{

public:
	enum class eCarNamesValues { a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z };
	Car(int locationX = 0, int locationY = 0, int location = 0, eCarNamesValues carName = static_cast<eCarNamesValues>(calculateName())) :
		_locationX(locationX),_locationY(locationY),_location(location), _carName(carName) {
		_numOfCars++; 
	}

	eCarNamesValues getCarName() const { return _carName; }
	void seCarName(eCarNamesValues carName) { _carName = carName; }
	char getCharFromEnum();

private:
	static int calculateName();

	int _locationX;
	int _locationY;
	int _location;
	eCarNamesValues _carName;
	static int _numOfCars;
	static constexpr int NUM_OF_LETTERS = 26;




};

