#ifndef IMAGE_ENCRYPTOR_INTERFACE_TEST_CPP
#define IMAGE_ENCRYPTOR_INTERFACE_TEST_CPP

#include <ConstData/ConstData.hpp>
#include <ImageEncryptor/ImageEncryptorInterface.hpp>
#include <MessageSizeFinder/MessageSizeFinder.hpp>
#include <PixelStrategy/WriteStrategy.hpp>
#include <SimpleConverter/SimpleConverter.hpp>
#include <Utils/Utils.hpp>
#include <utility>

namespace NsImageEncryptor {

void ImageEncryptorInterface::setStrategy(
    std::shared_ptr<NsPixelStrategy::WriteStrategy> s) {
  strategy = s;
}

void ImageEncryptorInterface::encryptMarker() {
  /*
    Encrypt SteganoImages marker to the into the first bytes of the image
  */
  using namespace NsConstData;

  const std::string marker(ConstData::instance().steganoMarker());
  strategy->setMessage(marker);
  NsRange::RangeFactory rangeFactory(handler->getNumOfPixels());
  auto range = rangeFactory.getRange(marker, ConstData::instance().msgMarkerStartPoint());
  handler->applyToEveryPixelInRangeRaw(strategy, range.start(), range.end());
}

void ImageEncryptorInterface::encryptSize(const size_t size) {
  /*
    Format of size to be encrypted:
    - 8 digits as text, always
    - if the size is shorter than 8 digits, add 0s to the front
    Example:
      size = 324, then string representation: 00000324
  */
  using namespace NsConstData;
  const size_t numberOfZeros = ConstData::instance().msgSizeSize() - NsUtils::digits(size);
  if (numberOfZeros < 0) {
    throw std::runtime_error("The message is too big!");
  }
  std::string temp(numberOfZeros, 0);

  NsSimpleConverter::SimpleConverter converter;
  const auto sizeStr = temp + converter.toString(size);
  strategy->setMessage(sizeStr);

  NsRange::RangeFactory rangeFactory(handler->getNumOfPixels());
  auto range =
      rangeFactory.getRange(sizeStr, ConstData::instance().getSteganoMarkerSizeInBits());

  handler->applyToEveryPixelInRangeRaw(strategy, range.start(), range.end());
}

void ImageEncryptorInterface::encrypt(const std::string &message) {
  encryptMarker();
  encryptSize(message.size());
  encryptData(message);
}

} // namespace NsImageEncryptor

#endif
