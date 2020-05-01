#ifndef CONST_DATA_HPP
#define CONST_DATA_HPP

namespace NsConstData {

const int bitsInByte = 8;
const int msgSizeStartPoint = 0; // where size information starts
const int msgBodyStartPoint = sizeof(size_t) * bitsInByte; // where message starts

}


#endif