#ifndef IMAGE_ENCRYPTOR_CPP
#define IMAGE_ENCRYPTOR_CPP

#include <utility>
#include <ImageEncryptor/ImageEncryptor.hpp>
#include <ParallelEncoder/ParallelEncoder.hpp>

namespace NsImageEncryptor {

using namespace NsConstData;

ImageEncryptor::ImageEncryptor(const std::string & imagePath, const std::string & pathToWrite) :
    imageHandler(imagePath, pathToWrite), messageLengthThreshold(100)
{}

ImageEncryptor::~ImageEncryptor() {}

void ImageEncryptor::encrypt(const std::string & message, const int startPoint) {
    const auto range = getMessageRange(message, startPoint);
    int index = 0;

    auto putMessageBitIntoPixel = [&](unsigned char & byte){
        // get message byte value, current bit number and bit value
        const unsigned char tmp = message.at(index/bitsInByte);
        const int bitNum = index % bitsInByte;
        const bool val = checkBit(tmp, bitNum);
        byte = setFirstBit(byte, val);
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
    using namespace NsConstData;
    using namespace NsParallelEncoder;

    const size_t sz = message.size() * bitsInByte;
    encodeMessageSize(sz, msgSizeStartPoint);
    if(message.length() < messageLengthThreshold) {
        encrypt(message, msgBodyStartPoint);
    } else {
        ParallelTask task(&ImageEncryptor::encrypt, this, message, msgBodyStartPoint);
        std::vector<decltype(task)> tasks; 
        tasks.push_back(task);
        ParallelEncoder parallelEncoder(tasks);
    }
}



}



#endif