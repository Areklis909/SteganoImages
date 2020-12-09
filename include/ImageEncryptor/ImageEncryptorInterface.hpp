#ifndef IMAGE_ENCRYPTOR_INTERFACE
#define IMAGE_ENCRYPTOR_INTERFACE

#include <ConstData/ConstData.hpp>
#include <ImageHandler/ImageHandlerInterface.hpp>
#include <Range/RangeFactory.hpp>
#include <PixelStrategy/WriteStrategy.hpp>
#include <memory>
#include <string>

namespace NsImageEncryptor {

class ImageEncryptorInterface {

protected:
  std::unique_ptr<NsImageHandler::ImageHandlerInterface> handler;
  std::shared_ptr<NsPixelStrategy::WriteStrategy> strategy;
public:
  ImageEncryptorInterface(
      std::unique_ptr<NsImageHandler::ImageHandlerInterface> h)
      : handler(std::move(h)) {}
  virtual ~ImageEncryptorInterface() = default;

  virtual void encryptData(const std::string &message) = 0;

  void setStrategy(std::shared_ptr<NsPixelStrategy::WriteStrategy> s);

  void encryptMarker();

  void encryptSize(const size_t size);

  void encrypt(const std::string &message);
};

} // namespace NsImageEncryptor

#endif