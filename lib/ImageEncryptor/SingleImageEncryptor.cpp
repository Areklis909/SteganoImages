#include <ImageEncryptor/SingleImageEncryptor.hpp>
#include <PixelStrategy/EncryptPixel.hpp>

namespace NsImageEncryptor {

SingleImageEncryptor::SingleImageEncryptor(
    std::unique_ptr<NsImageHandler::ImageHandlerInterface> h)
    : ImageEncryptorInterface(std::move(h)) {}

void SingleImageEncryptor::encryptData(const std::string &message) {
  using namespace NsConstData;
  NsRange::RangeFactory rangeFactory(handler->getNumOfPixels());
  auto range = rangeFactory.getRange(message, msgSizeMarkerSizeInBits + handler->getSteganoMarkerSizeInBits());
  handler->applyToEveryPixelInRangeRaw(
      std::make_unique<NsPixelStrategy::EncryptPixel<std::string>>(message), range.start(),
      range.end());
}

} // namespace NsImageEncryptor