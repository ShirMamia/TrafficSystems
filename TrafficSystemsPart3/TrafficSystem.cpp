#include <string>
#include <fstream>
#include "TrafficSystem.h" 
#include "street.h"
#include "CarsManagment.h"

using namespace std;

string TrafficSystem::getTextForEnumGuiValues(int enumVal) const {
    switch (enumVal) {
    case RED_LIGHT:
        return "R";
    case JUNCTION:
        return "+";
    case SPACE_BETWEEN_CELLS:
        return " ";
    case EMPTY_CELL:
        return "-";

    }
}

void TrafficSystem::parseFirstLine(const string &firstLine) {
    int matrix_rows = stoi(firstLine.substr(0, firstLine.find(" ")));
    int matrix_cols = stoi(firstLine.substr(firstLine.find(" ") + 1));
    setMatrixDimensions(matrix_rows, matrix_cols);
}
void TrafficSystem::setMatrixRows(int rows) {
    _matrix_rows = rows;
}
void TrafficSystem::setMatrixCols(int cols) {
    _matrix_cols = cols;
}
int TrafficSystem::calculateGuiMatrixDimension(int num) const {
    return 2 * num - 1;
}
void TrafficSystem::readStreets(ifstream& file, string& line) {
    int count = 0;
    int x = 0;
    int y = 0;
    string street_name;
    int street_length = 0;
    Street::eDirection d = Street::eDirection::HORIZONTAL; //default value
    while (getline(file, line)) {
        switch (count) {
        case 0:
            x = stoi(line.substr(0, line.find(" ")));
            y = stoi(line.substr(line.find(" ") + 1, line.find(" ") + 1));
            break;
        case 1:
            street_name = line;
            break;
        case 2:
            street_length = stoi(line);
            break;

        case 3:
            stoi(line) == 0? d = Street::eDirection::HORIZONTAL : d = Street::eDirection::VERTICAL;
            break;
        }
        int org_count = count;
        count++;
        count = count % 4;
        if (org_count != 3) { continue; }

        //build the matrix
        Street st(x, y, street_name, street_length, d);
        _allStreets.push_back(st);
    }
}
void TrafficSystem::setMatrixDimensions(int rows, int cols){
    setMatrixRows(rows);
    setMatrixCols(cols);
}
void TrafficSystem::setGuiDimensions()
{
    _gui_rows = calculateGuiMatrixDimension(_matrix_rows);
    _gui_cols = calculateGuiMatrixDimension(_matrix_cols);

}

void TrafficSystem::setGuiVector2(int i, int j, int id)
{
    if (_gui_vector[i][j] == getTextForEnumGuiValues(eGuiValues::EMPTY_CELL)) {
        _gui_vector[i][j] = Street::getLetterFromId(id);
    }
    else {
        _gui_vector[i][j] = getTextForEnumGuiValues(eGuiValues::JUNCTION);
    }
}
void TrafficSystem::setGuiVector(int i, int j, int id , Street::eDirection direction)
{
    if (_gui_vector[2*i][2*j] == getTextForEnumGuiValues(eGuiValues::EMPTY_CELL)) {
        _gui_vector[2*i][2*j] = Street::getLetterFromId(id);
        if (direction == Street::eDirection::HORIZONTAL) {
           // _gui_vector[2 * i][2 * j + 1] = Street::getLetterFromId(id);
           //int currentStreetLength =  _matrix[i][j].getHorizontalSt()->getStreet_length();
           int currentStreetLength = _matrix[i][j].getHorizontalSt()->lengthOfCells();
           int curentCellNumber = _matrix[i][j].getHorizontalCellNumber();
           if (curentCellNumber != currentStreetLength - 1) { //not last element
             _gui_vector[2 * i][2 * j + 1] = Street::getLetterFromId(id);
           }

        }
        else if (direction == Street::eDirection::VERTICAL) {
            _gui_vector[2 * i+1][2 * j] = Street::getLetterFromId(id);

        }
    }
    else {
        _gui_vector[2*i][2*j] = getTextForEnumGuiValues(eGuiValues::JUNCTION);
    }
}
TrafficSystem::TrafficSystem(const string& fileName) {

    // open file to read
    ifstream file;
    file.open(fileName);
    string line;

     //read the first line
    getline(file, line); 

    //set the dimensions
    parseFirstLine(line);

    //read the file and insert the streets to the vector
    readStreets(file, line);
    
    // Close the file 
    file.close();

    populateMatrices();

    CarsManagment::CarsManagment(_matrix,_matrix_rows,_matrix_cols);
}
TrafficSystem::~TrafficSystem() {
    //free _matrix
    for (int i = 0; i < _matrix_rows; i++) {
        delete[] _matrix[i];
    }
    delete[] _matrix;
}
int TrafficSystem::getColorNumber(const string& idString) const
{
    int id = Street::getEnumFromLetter(idString);
    int color = id % NUMBER_OF_COLORS;
    return getColorFromEnum(static_cast<eColorValues>(color));
}

void TrafficSystem::drawColor(int backgroundColor, char token) const {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_INTENSITY | backgroundColor);
    std::cout << token;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN);
}
int TrafficSystem::getColorFromEnum(eColorValues color) const{
    static std::map<eColorValues, int> EnumColorToIntValue{
       {LIGHT_BLUE, 50} , {BLUE,150} , {YELLOW,225} , {GREEN,170} , {WHITE,250} , {DARK_PINK,210} , {GRAY,130}
    };
    auto x = EnumColorToIntValue.find(color);
    if (x != std::end(EnumColorToIntValue)) {
        return x->second;
    }
}
void TrafficSystem::printCell(int i, int j, bool isFirst) const
{
    int color = 0;
    bool isJunctionOrEmptyCell = (_gui_vector[i][j] == getTextForEnumGuiValues(eGuiValues::EMPTY_CELL) || _gui_vector[i][j] == getTextForEnumGuiValues(eGuiValues::JUNCTION));
    bool isSpaceBetweenCells = _gui_vector[i][j] == getTextForEnumGuiValues(eGuiValues::SPACE_BETWEEN_CELLS);
    bool isRed = _gui_vector[i][j] == getTextForEnumGuiValues(eGuiValues::RED_LIGHT);
    bool hasColor = !isJunctionOrEmptyCell && !isSpaceBetweenCells;
    bool areEven = (i % 2 == 0) && (j % 2 == 0);
    bool hasHorizontalCar = _matrix[i/2][j/2].getHorizontalCar()!= nullptr;
    bool hasVerticalCar = _matrix[i/2][j/2].getVerticalCar() != nullptr;
    bool hasCar = areEven && (hasHorizontalCar || hasVerticalCar);
    if (isRed) {
        color = _trafficLightColor;
    }
    else if (hasColor) { //has color which is not red
        color = getColorNumber(_gui_vector[i][j]);
    }
    if (isFirst) {
        printCellAtFirst(hasColor, color, i , j);
    }
    else {
        printCellAtMiddle(hasColor, color, isRed, hasCar, i , j);
    }
}
void TrafficSystem::printCellAtFirst(bool hasColor, int color, int i, int j) const
{
    char spaceToken = ' ';
    if (hasColor) {
        std::cout << " " << "|" << " ";
        drawColor(color, spaceToken);
        drawColor(color, spaceToken);
    }
    else {
        std::cout << " " << "|" << " " << _gui_vector[i][j] << " ";
    }
}

void TrafficSystem::printCellAtMiddle(bool hasColor, int color, bool isRed, bool hasCar, int i, int j) const
{
    char token = ' ';
    char spaceToken = ' ';
    
    if (hasCar) {
        bool hasHorizontalCar = _matrix[i / 2][j / 2].getHorizontalCar() != nullptr;
        bool hasVerticalCar = _matrix[i / 2][j / 2].getVerticalCar() != nullptr;
        if (hasHorizontalCar) {
            Car* horizontalCar = _matrix[i / 2][j / 2].getHorizontalCar();
            token = horizontalCar->getCharFromEnum();
        }
        else if (hasVerticalCar) {
           // token = _matrix[i / 2][j / 2].getVerticalCar()->getCharFromEnum(_matrix[i / 2][j / 2].getVerticalCar()->getCarName());
        }

    }
    if (hasColor) {
        if (_matrix[i / 2][j / 2].getVerticalSt() != nullptr) { // is vertical
            std::cout << " ";
            drawColor(color, spaceToken);
            drawColor(color, spaceToken);
        }
        else {
            if (isRed) {
                std::cout << " ";
                drawColor(color, spaceToken);
                drawColor(color, spaceToken);

            }
            else {
                drawColor(color, token);
                drawColor(color, spaceToken);
                drawColor(color, spaceToken);
            }
        }
    }
    else {
        std::cout << " " << _gui_vector[i][j] << " ";

    }
}

void TrafficSystem::showRoads() const {
    std::cout << "  " << string(_gui_cols * 3, '_') << endl;
    for (int i = 0; i < _gui_rows; i++) {
        printCell(i, 0, true); // is first
        for (int j = 1; j < _gui_cols; j++) {
            printCell(i, j);
        }
        std::cout << "|" << endl;
    }
    std::cout << "  " << string(_gui_cols * 3, '_') << endl;
}
void TrafficSystem::initializeGuiVector()
{
    // set the dimensions of the gui matrix
    setGuiDimensions();

    // initialize the gui vector

    for (int i = 0; i < _gui_rows; i++)
    {
        // construct a vector of strings with given default value
        std::vector<string> v;
        for (int j = 0; j < _gui_cols; j++)
            v.push_back(" ");

        // push back above one-dimensional vector
        _gui_vector.push_back(v);
    }

    // populate the gui vector
    for (int i = 0; i < _gui_rows; i++) {
        for (int j = 0; j < _gui_cols; j++) {
            if (i % 2 == 0 && j % 2 == 0) {
                _gui_vector[i][j] = getTextForEnumGuiValues(eGuiValues::EMPTY_CELL);
            }
            else {
                _gui_vector[i][j] = getTextForEnumGuiValues(eGuiValues::SPACE_BETWEEN_CELLS);
            }
        }
    }
}
void TrafficSystem::populateMatrices() {

    // create the dynamic allocation of the matrix
    _matrix = new Cell * [_matrix_rows];
    for (int i = 0; i < _matrix_rows; i++) {
        _matrix[i] = new Cell[_matrix_cols];
    }
    initializeGuiVector();

    // loop over the streets and insert them to the matrices
    int allStreets_size = _allStreets.size();
    for (int i = 0; i < allStreets_size; i++)
    {
        Street* current_street = &(_allStreets.at(i));
        int x = current_street->getX();
        int y = current_street->getY();
        int length = current_street->lengthOfCells();

        // Horizontal
        if (current_street->getDirection() == Street::eDirection::HORIZONTAL) {
            int j = y;
            for (int k = 0; k < length; k++) {
                _matrix[x][j].setHorizontal(current_street,k);
                //setGuiVector2(2 * x, 2 * j, current_street->getId());
                setGuiVector(x,j, current_street->getId(),Street::eDirection::HORIZONTAL);

                j++;
            }
        }
        // Vertical
        else if (current_street->getDirection() == Street::eDirection::VERTICAL) {
            int j = x;
            for (int k = 0; k < length; k++) {
                _matrix[j][y].setVertical(current_street, k);
                if (_matrix[j][y].getHorizontalSt() != nullptr) {
                    _matrix[j][y].setIsJunction(true); // we have a junction
                }
                //setGuiVector2(2 * j, 2 * y, current_street->getId());
                setGuiVector(j, y, current_street->getId(), Street::eDirection::VERTICAL);
                j++;
            }
        }
    }
    addTrafficLights();
}
void TrafficSystem::addTrafficLights() {
    for (int i = 0; i < _gui_rows; i++) {
        for (int j = 0; j < _gui_cols; j++) {
            if (_gui_vector[i][j] == getTextForEnumGuiValues(eGuiValues::JUNCTION)) {
                if (i > 0) {
                    _gui_vector[i - 1][j] = getTextForEnumGuiValues(eGuiValues::RED_LIGHT);
                }
                if (i < _gui_rows - 1) {
                    _gui_vector[i + 1][j] = getTextForEnumGuiValues(eGuiValues::RED_LIGHT);
                }
                if (j > 0) {
                    _gui_vector[i][j - 1] = getTextForEnumGuiValues(eGuiValues::RED_LIGHT);
                }
                if (j < _gui_cols - 1) {
                    _gui_vector[i][j + 1] = getTextForEnumGuiValues(eGuiValues::RED_LIGHT);
                }
            }
        }
    }
}