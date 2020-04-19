#ifndef TEXT_TO_BITS_CONVERTER
#define TEXT_TO_BITS_CONVERTER

#include <ConverterInterface/ConverterInterface.hpp>
#include <CharBit/CharBit.hpp>
#include <string>
#include <iostream>
#include <algorithm>

namespace NsTextToBitsConverter {

class TextToBitsConverter : public NsConverterInterface::ConverterInterface<TextToBitsConverter> {

public:
    TextToBitsConverter() {};
    ~TextToBitsConverter() {};
    
    template<typename Input, typename Output>
    Output convert(const Input & message) {
        Output ret;
        std::cout << "Text to bits: \n";
        for(const auto character : message) {
            convertSignToBits(ret, character);
        }
        std::cout << '\n';
        return ret;
    }

    template<typename Container>
    void convertSignToBits(Container & container, const char sign) {
        using NsCharBit::CharBit;

        const int bitsInByte = 8;
        for(int i = 0; i < bitsInByte; ++i) {
            CharBit bit((sign & (1 << i)) ? true : false);
            std::cout << bit << " ";
            container.push_back(std::move(bit));
        }
        std::cout << '\n';
    }
};

}

#endif