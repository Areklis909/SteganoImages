#ifndef ENCRYPT_PIXEL_HPP
#define ENCRYPT_PIXEL_HPP

#include "WriteStrategy.hpp"
#include <ConstData/ConstData.hpp>
#include <BitwiseOperations/BitwiseOperations.hpp>

namespace NsPixelStrategy {

class EncryptPixel : public WriteStrategy,
                     public NsBitwiseOperations::BitwiseOperations {

public:
  EncryptPixel() = default;
  ~EncryptPixel() = default;

  virtual char pixelOperation(char byte) override {
    using namespace NsConstData;
    const unsigned char tmp = message.at(index / ConstData::instance().bitsInByte());
    const int bitNum = index % ConstData::instance().bitsInByte();
    const bool val = checkBit(tmp, bitNum);
    byte = setFirstBit(byte, val);
    ++index;
    return byte;
  }
};

} // namespace NsPixelStrategy

#endif