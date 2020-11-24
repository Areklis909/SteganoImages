#ifndef IMAGE_ENCRYPTOR_FACTORY_INTERFACE_HPP
#define IMAGE_ENCRYPTOR_FACTORY_INTERFACE_HPP

#include <ImageHandler/ImageHandlerInterface.hpp>
#include <ImageEncryptor/ImageEncryptorInterface.hpp>
#include <memory>

namespace NsImageEncryptor {

class ImageEncryptorFactoryInterface {

public:
    ImageEncryptorFactoryInterface() = default;
    ~ImageEncryptorFactoryInterface() = default;
    
    virtual std::unique_ptr<ImageEncryptorInterface>
     get(const std::string & className, std::unique_ptr<NsImageHandler::ImageHandlerInterface> handler) = 0;
};


}

#endif