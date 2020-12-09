#ifndef READ_PIXEL_HPP
#define READ_PIXEL_HPP

#include <PixelStrategy/PixelStrategy.hpp>
#include <BitwiseOperations/BitwiseOperations.hpp>
#include <string>
#include <sstream>

namespace NsPixelStrategy {

class ReadPixel : public PixelStrategy, NsBitwiseOperations::BitwiseOperations {

  int index = 0;
  unsigned char currentCharacter = 0;
  std::stringstream stream;
public:
  char pixelOperation(char byte) override;
  std::string getMessage();
};

} // namespace NsPixelStrategy

#endif