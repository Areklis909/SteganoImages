#include <ImageEncryptor/ImageEncryptorFactory.hpp>
#include <ImageEncryptor/ImageEncryptorManager.hpp>
#include <ImageHandler/ImageHandler.hpp>

namespace NsImageEncryptor {

ImageEncryptorManager::ImageEncryptorManager(const std::string &in,
                                             const std::string &out)
    : input(in), output(out) {}

void ImageEncryptorManager::setEncryptor(
    std::unique_ptr<ImageEncryptorInterface> enc) {
  encryptor = std::move(enc);
}

void ImageEncryptorManager::setInput(const std::string &in) { input = in; }

void ImageEncryptorManager::setOutput(const std::string &out) { output = out; }

size_t ImageEncryptorManager::getMsgLengthLimit() { return 1000; }

void ImageEncryptorManager::doWork(const std::string &msg) {

  if (encryptor == nullptr) {
    ImageEncryptorFactory factory;
    std::string encType;
    if (msg.size() > getMsgLengthLimit()) {
      encType = "MULTI";
    } else {
      encType = "SINGLE";
    }
    encryptor =
        factory.get(encType, std::make_unique<NsImageHandler::ImageHandler>(input, output));
  }

  encryptor->encrypt(msg);
}

} // namespace NsImageEncryptor