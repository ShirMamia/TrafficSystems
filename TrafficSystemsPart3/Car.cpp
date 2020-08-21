#include "Car.h"
int Car::_numOfCars = 0;
int Car::calculateName() {
	return (_numOfCars ) % NUM_OF_LETTERS;
}

char Car::getCharFromEnum() {
    static std::map<eCarNamesValues, char> CharFromEnum{
       {eCarNamesValues::a,'a'} , {eCarNamesValues::b,'b'} , {eCarNamesValues::c,'c'} , {eCarNamesValues::d,'d'} ,
       {eCarNamesValues::e,'e'} , {eCarNamesValues::f,'f'} , {eCarNamesValues::g,'g'} , {eCarNamesValues::h,'h'},{eCarNamesValues::i,'i'},
       {eCarNamesValues::j,'j'} , {eCarNamesValues::k,'k'} , {eCarNamesValues::l,'l'} , {eCarNamesValues::m,'m'} ,
       {eCarNamesValues::n,'n'} , {eCarNamesValues::o,'o'} , {eCarNamesValues::p,'p'},{eCarNamesValues::q,'q'},{eCarNamesValues::r,'r'},
       {eCarNamesValues::s,'s'}, {eCarNamesValues::t,'t'},{eCarNamesValues::u,'u'},{eCarNamesValues::v,'v'},{eCarNamesValues::w,'w'},
       {eCarNamesValues::x,'x'}, {eCarNamesValues::y,'y'}, {eCarNamesValues::z,'z'}

    };
    auto x = CharFromEnum.find(_carName);
    if (x != std::end(CharFromEnum)) {
        return x->second;
    }
}