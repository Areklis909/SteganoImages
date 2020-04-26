#ifndef IMAGE_ENCRYPTOR_CPP
#define IMAGE_ENCRYPTOR_CPP

#include <ImageEncryptor/ImageEncryptor.hpp>
#include <CharBit/CharBit.hpp>

#include <utility>

namespace NsImageEncryptor {

using namespace NsConstData;

ImageEncryptor::ImageEncryptor(const std::string & imagePath, const std::string & pathToWrite) :
    imageHandler(imagePath, pathToWrite)
{

}

ImageEncryptor::~ImageEncryptor() {}

void ImageEncryptor::encryptTest(const std::string & message) {
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

void ImageEncryptor::encrypt(const std::string & message, const int startPoint) {
    const auto range = getMessageRange(message, startPoint);
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
    imageHandler.applyToEveryPixelInRangeRaw(putMessageBitIntoPixel, range.first, range.second);
}

std::pair<int, int> ImageEncryptor::getMessageRange(const std::string & message, const int start) {
    const int msgSizeInBits = message.size() * bitsInByte;
    const int allPixels = imageHandler.getNumOfPixels();
    if(msgSizeInBits > allPixels) {
        throw std::runtime_error("Message is too big!");
    }
    return std::make_pair(start, start + msgSizeInBits);
}

void ImageEncryptor::encryptData(const std::string & message) {
    encrypt(message.size(), msgSizeStartPoint);
    // encrypt(message, msgBodyStartPoint);
}



}



#endif