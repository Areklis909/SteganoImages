#ifndef CHAR_BIT_CPP
#define CHAR_BIT_CPP

#include <CharBit/CharBit.hpp>

namespace NsCharBit {


CharBit::CharBit(const BIT_VALUE value) : value(value) {};

CharBit::CharBit(const bool value) : value((value == true) ? BIT_VALUE::TRUE : BIT_VALUE::FALSE) {};

bool CharBit::get() const {
    return static_cast<bool>(value);
}

CharBit::BIT_VALUE CharBit::getValue() const {
    return value;
}

bool CharBit::operator==(const CharBit & other) const {
    return other.get() == this->get();
}

void CharBit::operator=(const CharBit & other) {
    this->value = other.getValue();
}

CharBit::operator bool() const {
    return (value == BIT_VALUE::TRUE) ? true : false;
}

std::ostream & operator<<(std::ostream & out, const CharBit bit) {
    out << static_cast<bool>(bit);
    return out;
}


}

#endif