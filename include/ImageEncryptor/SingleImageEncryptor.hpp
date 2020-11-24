#ifndef SINGLE_IMAGE_ENCRYPTOR
#define SINGLE_IMAGE_ENCRYPTOR

#include <ImageEncryptor/ImageEncryptorInterface.hpp>

namespace NsImageEncryptor {

class SingleImageEncryptor : public ImageEncryptorInterface {

public:
    SingleImageEncryptor(std::unique_ptr<NsImageHandler::ImageHandlerInterface> h);
    ~SingleImageEncryptor() = default;
    void encryptData(const std::string &message) override;
};

}


#endif