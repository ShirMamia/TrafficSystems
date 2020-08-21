#include "street.h"
#include <iostream>

//street:
int Street::idCount = 1;
int Street::lengthOfCells() const {
	return _street_length / RATIO;
}
Street::Street(int x, int y, const string& name, int street_length, eDirection d) :_x(x), _y(y), _name(name), _street_length(street_length),
_eIdValues(static_cast<eIdValues>(idCount)), _eDirection(d) {
	idCount++;
}
string Street::getLetterFromId(int id) {
    switch (id) {
    case A:
        return "A";
    case B:
        return "B";
    case C:
        return "C";
    case D:
        return "D";
    case E:
        return "E";
    case F:
        return "F";
    case G:
        return "G";
    case H:
        return "H";
    case I:
        return "I";
    case J:
        return "J";
    case K:
        return "K";
    case L:
        return "L";
    case M:
        return "M";
    case N:
        return "N";
    case O:
        return "O";
    case P:
        return "P";
    case Q:
        return "Q";
    case R:
        return "R";
    case S:
        return "S";
    case T:
        return "T";
    case U:
        return "U";
    case V:
        return "V";
    case W:
        return "W";
    case X:
        return "X";
    case Y:
        return "Y";
    case Z:
        return "Z";
    }
}
int Street::getEnumFromLetter(const string& id){
        static std::map<std::string, eIdValues> stringToEnum{
           {"A", A} , {"B",B} , {"C",C} , {"D",D} , {"E",E} , {"F",F} , {"G",G} , {"H",H},
           {"I", I } , {"J",J} , {"K",K} , {"L",L} , {"M",M} , {"N",N} , {"O",O} , {"P",P},
           {"Q", Q } , {"R",R} , {"S",S} , {"T",T}  , {"U",U} ,{"V",V} , {"W",W} , {"X",X},
           { "Y", Y } , {"Z", Z}
        };
        auto x = stringToEnum.find(id);
        if (x != std::end(stringToEnum)) {
            return x->second;
        }
}
