#ifndef IMAGE_ENCRYPTOR_CPP
#define IMAGE_ENCRYPTOR_CPP

#include <ImageEncryptor/ImageEncryptor.hpp>
#include <CharBit/CharBit.hpp>

namespace NsImageEncryptor {


ImageEncryptor::ImageEncryptor(const std::string & imagePath, const std::string & pathToWrite) :
    imageHandler(imagePath, pathToWrite)
{

}

ImageEncryptor::~ImageEncryptor() {}

void ImageEncryptor::encrypt(const std::string & message) {
    using NsCharBit::CharBit;
    
    auto bitStream = converter.convert<std::string, std::vector<CharBit>>(message);
    int index {0};
    auto incorporateBitsIntoPixels = [&](unsigned char & byte){
        const int8_t lsbMask = 0x1;
        const bool val = static_cast<bool>(bitStream.at(index++));
        const int8_t value = (val << 0);

        byte &= (~lsbMask);
        byte |= (value);
    };
    imageHandler.applyToEveryPixel(incorporateBitsIntoPixels);

}

}



#endif