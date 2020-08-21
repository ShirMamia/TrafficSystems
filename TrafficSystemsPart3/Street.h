#pragma once
#include <iostream>
#include <string>
#include <windows.h>
#include <map>

using namespace std;

class Street {


public:
	enum class eDirection { HORIZONTAL, VERTICAL};
	enum eIdValues { A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z };


	Street(int x, int y, const string& name, int street_length, eDirection d);
	int getX() const { return _x; }
	int getY() const { return _y; }
	const string &getName() { return _name; }
	int getStreet_length() const { return _street_length; }
	int getId() const { return _eIdValues; }
	void setId(int id) { _eIdValues = static_cast<eIdValues>(id); }
	eDirection getDirection() const { return _eDirection; } 
	void setDirection(eDirection d) { _eDirection = d; }
	int lengthOfCells() const;
	static string getLetterFromId(int id);
	static int getEnumFromLetter(const string& id);

private:
	int _x;
	int _y;
	string _name;
	int _street_length;
	eDirection _eDirection;
	static int idCount;
	static constexpr int RATIO = 200;
	eIdValues _eIdValues;


};
