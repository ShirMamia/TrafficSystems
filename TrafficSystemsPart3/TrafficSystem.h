#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <windows.h>
#include <map>
#include "Cell.h"
using namespace std;

class TrafficSystem {

private: 
	const int _trafficLightColor = 200;
	int _matrix_rows;
	int _matrix_cols;
	Cell** _matrix;

	int _gui_rows;
	int _gui_cols;
	std::vector<std::vector<string>> _gui_vector;

	vector<Street> _allStreets;
	enum eGuiValues { RED_LIGHT , JUNCTION , SPACE_BETWEEN_CELLS, EMPTY_CELL};
	eGuiValues _eGuiValues;

	//enum eColorValues { LIGHT_BLUE = 310 , BLUE = 400, YELLOW = 870, GREEN = 300, WHITE = 500, DARK_PINK = 600, GRAY = 900};
	enum eColorValues {LIGHT_BLUE, BLUE, YELLOW, GREEN, WHITE, DARK_PINK, GRAY};
	eColorValues _eColorValues;



	//methods
	void parseFirstLine(const string& firstLine);
	void setGuiDimensions();
	string getTextForEnumGuiValues(int enumVal) const; 
	void readStreets(ifstream& file, string& line);
	void setMatrixRows(int rows);
	void setMatrixCols(int cols);
	void setMatrixDimensions(int rows, int cols);
	int calculateGuiMatrixDimension(int num) const;
	int getColorFromEnum(eColorValues color) const;

	
	// gui vector methods
	void initializeGuiVector();
	void populateMatrices();
	void addTrafficLights();
	void setGuiVector2(int i, int j, int id);
	void setGuiVector(int i, int j, int id, Street::eDirection direction);
	int getColorNumber(const string& idString) const;

	//cars
	void addCarToTheBegginingOfEachStreet();

	//print methods
	void printCell(int i, int j, bool isFirst = false) const;
	void printCellAtFirst(bool hasColor, int color, int i, int j, char token) const; // not in use
	void executePrintCell(bool isFirst,bool hasColor, int color,bool isRed, int i, int j ,char token) const;

public:
	TrafficSystem(const string& fileName);
	~TrafficSystem();

	void drawColor(int backgroundColor, char token) const;
	void showRoads() const;
	static constexpr int NUMBER_OF_COLORS = 7;







};
