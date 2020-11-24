#ifndef IMAGE_ENCRYPTOR_FACTORY
#define IMAGE_ENCRYPTOR_FACTORY

#include <memory>
#include <ImageEncryptor/ImageEncryptorFactoryInterface.hpp>
#include <ImageHandler/ImageHandlerInterface.hpp>

namespace NsImageEncryptor {

class ImageEncryptorFactory : public ImageEncryptorFactoryInterface {

public:

    ImageEncryptorFactory() = default;
    ~ImageEncryptorFactory() = default;

    std::unique_ptr<ImageEncryptorInterface>
     get(const std::string & className, std::unique_ptr<NsImageHandler::ImageHandlerInterface> handler) override;

};

}
#endif