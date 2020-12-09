#include <ImageEncryptor/SingleImageEncryptor.hpp>
#include <PixelStrategy/PixelStrategy.hpp>

namespace NsImageEncryptor {

SingleImageEncryptor::SingleImageEncryptor(
    std::unique_ptr<NsImageHandler::ImageHandlerInterface> h)
    : ImageEncryptorInterface(std::move(h)) {}

void SingleImageEncryptor::encryptData(const std::string &message) {
  using namespace NsConstData;
  strategy->setMessage(message);
  NsRange::RangeFactory rangeFactory(handler->getNumOfPixels());
  auto range = rangeFactory.getRange(
      message, ConstData::instance().msgSizeMarkerSizeInBits() +
                   ConstData::instance().getSteganoMarkerSizeInBits());
  handler->applyToEveryPixelInRangeRaw(strategy, range.start(), range.end());
}

} // namespace NsImageEncryptor