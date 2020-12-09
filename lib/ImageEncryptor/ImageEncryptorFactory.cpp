#include <stdexcept>
#include <memory>
#include <ImageEncryptor/ImageEncryptorFactory.hpp>
#include <ImageEncryptor/SingleImageEncryptor.hpp>
#include <ImageEncryptor/MultiImageEncryptor.hpp>
#include <ImageHandler/ImageHandler.hpp>
#include <PixelStrategy/EncryptPixel.hpp>

namespace NsImageEncryptor {


std::unique_ptr<ImageEncryptorInterface> ImageEncryptorFactory::get(const std::string & className, std::unique_ptr<NsImageHandler::ImageHandlerInterface> handler) {

    std::unique_ptr<ImageEncryptorInterface> ret;
    if(className.compare("SINGLE") == 0) {
        ret = std::make_unique<SingleImageEncryptor>(std::move(handler));
    } else if(className.compare("MULTI") == 0) {
        ret = std::make_unique<MultiImageEncryptor>(std::move(handler));
    } else {
        throw std::runtime_error("Incorrect Encryptor type!");
    }
    ret->setStrategy(std::make_shared<NsPixelStrategy::EncryptPixel>());
    return ret;
}


}