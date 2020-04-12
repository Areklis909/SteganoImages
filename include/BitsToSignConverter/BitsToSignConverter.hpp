#ifndef BITS_TO_SIGN_CONVERTER
#define BITS_TO_SIGN_CONVERTER

#include <CharBit/CharBit.hpp>
#include <ConverterInterface/ConverterInterface.hpp>
#include <string>
#include <iostream>

namespace NsBitsToSignConverter {

class BitsToSignConverter : public NsConverterInterface::ConverterInterface<BitsToSignConverter> {


public:
    BitsToSignConverter() {};
    ~BitsToSignConverter() {};

    template<typename Input, typename Output>
    Output convert(const Input & input) {
        Output message;
        const int bitsInByte = 8;
        int index {0};
        typename Output::value_type character {0};
        for(const auto bit : input) {
            if(bit == true) {
                character |= (1 << index % bitsInByte);
            }
            if(++index % bitsInByte == 0) {
                message.push_back(character);
                character = 0;
            }
        }
        return message;
    }

};

}

#endif