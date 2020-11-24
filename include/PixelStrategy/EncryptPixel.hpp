#ifndef ENCRYPT_PIXEL_HPP
#define ENCRYPT_PIXEL_HPP

#include "PixelStrategy.hpp"
#include <ConstData/ConstData.hpp>
#include <BitwiseOperations/BitwiseOperations.hpp>

namespace NsPixelStrategy {

template <typename MessageType>
class EncryptPixel : public PixelStrategy,
                     public NsBitwiseOperations::BitwiseOperations {

  int index = 0;
  const MessageType message;

public:
  EncryptPixel(const MessageType &msg) : message(msg) {}

  virtual char pixelOperation(char byte) override {
    using namespace NsConstData;
    const unsigned char tmp = message.at(index / bitsInByte);
    const int bitNum = index % bitsInByte;
    const bool val = checkBit(tmp, bitNum);
    byte = setFirstBit(byte, val);
    ++index;
    return byte;
  }
};

} // namespace NsPixelStrategy

#endif