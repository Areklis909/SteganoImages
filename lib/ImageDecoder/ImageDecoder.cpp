#ifndef IMAGE_DECODER_CPP
#define IMAGE_DECODER_CPP

#include <ImageDecoder/ImageDecoder.hpp>
#include <NotSteganoException/NotSteganoException.hpp>
#include <utility>

namespace NsImageDecoder {

ImageDecoder::ImageDecoder(std::unique_ptr<NsImageHandler::ImageHandlerInterface> hdl) : handler(std::move(hdl)) {}

size_t ImageDecoder::getMessageSize() {
  using namespace NsConstData;

  size_t msgSize{0};
  // int32_t index{0};
  // auto readMsgSize = [&](const unsigned char byte) {
  //   const bool bitValue = checkFirstBit(byte);
  //   msgSize = setBit(msgSize, bitValue, index++);
  // };
  // image.applyToEveryPixelInRangeRaw(image.getSteganoMarkerSizeInBits(),
  //                                   image.getSteganoMarkerSizeInBits() + msgSizeMarkerSizeInBits);
  return msgSize;
}

std::string ImageDecoder::readMessage() {
  if(findSteganoMarker() == false) {
    throw NsNotSteganoException::NotSteganoException();
  }
  const size_t msgSize = getMessageSize();
  const std::string msg = getMessage(msgSize);
  return msg;
}

// std::string ImageDecoder::getContent(const size_t start,
//                                      const size_t messageSize) {
  // using namespace NsConstData;

  // std::stringstream stream;
  // unsigned char currentCharacter{0};
  // int32_t index{0};
  // auto assembleTheMessage = [&](const unsigned char byte) {
  //   const int bitNum = index % bitsInByte;
  //   const bool bitValue = checkFirstBit(byte);
  //   currentCharacter = setBit(currentCharacter, bitValue, bitNum);
  //   if (bitNum == bitsInByte - 1) {
  //     stream << currentCharacter;
  //     currentCharacter = 0;
  //   }
  //   ++index;
  // };
  // image.applyToEveryPixelInRangeRaw(start,
  //                                   start + messageSize);
//   return stream.str();
// }

bool ImageDecoder::findSteganoMarker() {
  using namespace NsConstData;
  return false;
  // const std::string marker = getContent(ConstData::instance().msgMarkerStartPoint(), ConstData::instance().getSteganoMarkerSizeInBits());
  // return marker.compare(ConstData::instance().steganoMarker()) == 0;
}

std::string ImageDecoder::getMessage(const size_t messageSize) {
  using namespace NsConstData;
  return {};
  // return getContent(ConstData::instance().getSteganoMarkerSizeInBits() + ConstData::instance().msgSizeMarkerSizeInBits(), messageSize);
}

} // namespace NsImageDecoder

#endif
