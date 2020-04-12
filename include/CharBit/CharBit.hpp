#ifndef CHAR_BIT_HPP
#define CHAR_BIT_HPP

#include <iostream>

namespace NsCharBit {

class CharBit {

public:
    enum BIT_VALUE : char {
        FALSE = 0,
        TRUE = 1
    };

    explicit CharBit(const BIT_VALUE value);
    explicit CharBit(const bool value);

    inline bool get() const;
    inline BIT_VALUE getValue() const;
    bool operator==(const CharBit & other) const;
    void operator=(const CharBit & other);
    operator bool() const;

    friend std::ostream & operator<<(std::ostream & out, const CharBit bit);

private:
    BIT_VALUE value;
};

}

#endif