#ifndef CONST_DATA_HPP
#define CONST_DATA_HPP

#include <cstddef>
#include <cstdint>

namespace NsConstData {

const int bitsInByte = 8;
const int msgMarkerStartPoint = 0;
const int msgSizeMarkerSizeInBits =
    sizeof(size_t) * bitsInByte; // where message starts

} // namespace NsConstData

#endif