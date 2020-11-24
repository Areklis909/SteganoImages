#ifndef IMAGE_ENCRYPTOR_INTERFACE_CPP
#define IMAGE_ENCRYPTOR_INTERFACE_CPP

#include <ConstData/ConstData.hpp>
#include <ImageEncryptor/ImageEncryptorInterface.hpp>
#include <MessageSizeFinder/MessageSizeFinder.hpp>
#include <SimpleConverter/SimpleConverter.hpp>
#include <Utils/Utils.hpp>
#include <PixelStrategy/EncryptPixel.hpp>

namespace NsImageEncryptor {

void ImageEncryptorInterface::encryptMarker() {
  /*
    Encrypt SteganoImages marker to the into the first bytes of the image
  */
  using namespace NsConstData;

  const auto marker = handler->getSteganoMarker();
  NsRange::RangeFactory rangeFactory(handler->getNumOfPixels());
  auto range = rangeFactory.getRange(marker, msgMarkerStartPoint);
  handler->applyToEveryPixelInRangeRaw(
      std::make_unique<NsPixelStrategy::EncryptPixel<std::string>>(marker), range.start(),
      range.end());
}

void ImageEncryptorInterface::encryptSize(const size_t size) {
  /*
    Format of size to be encrypted:
    - 8 digits as text, always
    - if the size is shorter than 8 digits, add 0s to the front
    Example:
      size = 324, then string representation: 00000324
  */
  const size_t numberOfZeros = NsConstData::msgSizeSize - NsUtils::digits(size);
  if (numberOfZeros < 0) {
    throw std::runtime_error("The message is too big!");
  }
  std::string temp(numberOfZeros, 0);

  NsSimpleConverter::SimpleConverter converter;
  auto sizeStr = temp + converter.toString(size);

  NsRange::RangeFactory rangeFactory(handler->getNumOfPixels());
  auto range = rangeFactory.getRange(sizeStr, handler->getSteganoMarkerSizeInBits());

  handler->applyToEveryPixelInRangeRaw(
      std::make_unique<NsPixelStrategy::EncryptPixel<std::string>>(sizeStr), range.start(),
      range.end());
}

void ImageEncryptorInterface::encrypt(const std::string &message) {
  encryptMarker();
  encryptSize(message.size());
  encryptData(message);
}

} // namespace ImageEncryptorInterface

#endif
