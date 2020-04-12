#ifndef IMAGE_ENCRYPTOR_HPP
#define IMAGE_ENCRYPTOR_HPP

#include <ImageHandler/ImageHandler.hpp>
#include <TextToBitsConverter/TextToBitsConverter.hpp>

namespace NsImageEncryptor {

class ImageEncryptor {

    NsImageHandler::ImageHandler imageHandler;
    NsTextToBitsConverter::TextToBitsConverter converter;

public:
    ImageEncryptor(const std::string & imagePath, const std::string & pathToWrite);
    ~ImageEncryptor();

    void encrypt(const std::string & message);
};

}

#endif