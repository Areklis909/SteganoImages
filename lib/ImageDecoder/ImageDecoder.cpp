#ifndef IMAGE_DECODER_CPP
#define IMAGE_DECODER_CPP

#include <ImageDecoder/ImageDecoder.hpp>
#include <sstream>

namespace NsImageDecoder {

ImageDecoder::ImageDecoder(const std::string & imagePath) : image(imagePath) {

}

ImageDecoder::~ImageDecoder() {

}

size_t ImageDecoder::getMessageSize() {
    using namespace NsConstData;

    size_t msgSize {0};
    int32_t index {0};
    auto readMsgSize = [&](const unsigned char byte){
        const bool bitValue = checkFirstBit(byte);
        msgSize = setBit(msgSize, bitValue, index++);
    };

    image.applyToEveryPixelInRangeRaw(readMsgSize, msgSizeStartPoint, msgBodyStartPoint);
    return msgSize;
}

std::string ImageDecoder::readMessage() {
    const size_t msgSize = getMessageSize();
    const std::string msg = getMessage(msgSize);
    return msg;
}

std::string ImageDecoder::getMessage(const size_t messageSize) {
    using namespace NsConstData;

    std::stringstream stream;
    unsigned char currentCharacter {0};
    int32_t index {0};
    auto assembleTheMessage = [&](const unsigned char byte){
        const int bitNum = index % bitsInByte;
        const bool bitValue = checkFirstBit(byte);
        currentCharacter = setBit(currentCharacter, bitValue, bitNum);
        if(bitNum == bitsInByte - 1) {
            stream << currentCharacter;
            currentCharacter = 0;
        }
        ++index;
    };
    image.applyToEveryPixelInRangeRaw(assembleTheMessage, msgBodyStartPoint, msgBodyStartPoint + messageSize);
    return stream.str();
}

}

#endif
