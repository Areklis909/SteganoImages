#ifndef BITWISE_OPERATIONS_HPP
#define BITWISE_OPERATIONS_HPP

namespace NsBitwiseOperations {

class BitwiseOperations {

public:
    template<typename U>
    bool checkBit(const U data, const int bitNumber) {
        return (data & ((U)1 << bitNumber)) == ((U)1 << bitNumber);
    }

    template<typename U>
    bool checkFirstBit(const U data) {
        return checkBit(data, 0);
    }

    template<typename U>
    U setBit(const U currentValue, const bool bit, const int bitNumber) {
        return currentValue | ((U)bit << bitNumber);
    }

    uint8_t setBitWithMask(uint8_t byte, uint8_t mask, const bool value, const int bitNumber) {
        byte &= ~mask;
        return byte | (value << bitNumber);
    }

    uint8_t setFirstBit(uint8_t byte, const bool value) {
        return setBitWithMask(byte, 0x1, value, 0);
    }
};

}
#endif