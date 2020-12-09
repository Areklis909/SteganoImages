#include <ConstData/ConstData.hpp>
#include <PixelStrategy/ReadPixel.hpp>

namespace NsPixelStrategy {

char PixelStrategy::pixelOperation(char byte) {

  using namespace NsConstData;
  const int bitNum = index % ConstData::instance().bitsInByte();
  const bool bitValue = checkFirstBit(byte);
  currentCharacter = setBit(currentCharacter, bitValue, bitNum);
  if (bitNum == ConstData::instance().bitsInByte() - 1) {
    stream << currentCharacter;
    currentCharacter = 0;
  }
  ++index;
}

std::string PixelStrategy::getMessage() {
    return stream.str();
}


} // namespace NsPixelStrategy