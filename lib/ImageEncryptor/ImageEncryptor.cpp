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
    imageHandler.applyToEveryPixelRaw(incorporateBitsIntoPixels);
}

void ImageEncryptor::encrypt2(const std::string & message) {
    const int bitsInByte = 8;
    const int msgSizeInBits = message.size() * bitsInByte;
    const int allPixels = imageHandler.getNumOfPixels();

    if(msgSizeInBits > allPixels) {
        throw std::runtime_error("Message too big!");
    }

    const int start = 0;
    const int end = start + msgSizeInBits;

    std::cout << start << " " << end << '\n';
    int index = 0;
    auto putMessageBitIntoPixel = [&](unsigned char & byte){
        const int8_t lsbMask = 0x1;
        // get message byte value, current bit number and bit value
        const unsigned char tmp = message.at(index/bitsInByte);
        const int bitNum = index % bitsInByte;
        const int val = tmp & (1 << bitNum);

        const int8_t value = (val << 0);

        byte &= (~lsbMask);
        byte |= (value);

        ++index; 
    };

    imageHandler.applyToEveryPixelInRange(putMessageBitIntoPixel, start, end);
    // imageHandler.applyToEveryPixelInRangeRaw(putMessageBitIntoPixel, start, end);
}

}



#endif