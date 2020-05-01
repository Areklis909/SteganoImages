#ifndef IMAGE_ENCRYPTOR_HPP
#define IMAGE_ENCRYPTOR_HPP

#include <ImageHandler/ImageHandler.hpp>
#include <TextToBitsConverter/TextToBitsConverter.hpp>
#include <ConstData/ConstData.hpp>
#include <BitwiseOperations/BitwiseOperations.hpp> 
#include <type_traits>

namespace NsImageEncryptor {

class ImageEncryptor : public NsBitwiseOperations::BitwiseOperations {

    NsImageHandler::ImageHandler imageHandler;
    NsTextToBitsConverter::TextToBitsConverter converter;

    std::pair<int, int> getMessageRange(const std::string & message, const int start);

    template<typename T>
    std::pair<int, int> getMessageRange(T message, const int start) {
        using namespace NsConstData;

        const int msgSizeInBits = sizeof(message) * bitsInByte;
        const int allPixels = imageHandler.getNumOfPixels();
        if(msgSizeInBits > allPixels) {
            throw std::runtime_error("Message is too big!");
        }
        return std::make_pair(start, start + msgSizeInBits);
    }

    template<typename T>
    char * toBytes(T data) {
        T * ptr = static_cast<T *>(&data);
        void * dataBuf = static_cast<void *>(ptr);
        return static_cast<char *>(dataBuf);
    }

    void encrypt(const std::string & message, const int startPoint);

    template<typename T, 
        typename std::enable_if<std::is_pod_v<T>
        && !std::is_class_v<T>
        && !std::is_array_v<T> >::type* = nullptr>
    void encrypt(T message, const int startPoint) {
        using namespace NsConstData;

        const auto range = getMessageRange(message, startPoint);
        int index = 0;

        char * bytes = toBytes(message);
        auto putMessageBitIntoPixel = [&](unsigned char & byte){
            // get message byte value, current bit number and bit value
            const unsigned char tmp = bytes[index/bitsInByte];
            const int bitNum = index % bitsInByte;
            const bool val = checkBit(tmp, bitNum);
            byte = setFirstBit(byte, val);
            index++;
        };

        imageHandler.applyToEveryPixelInRangeRaw(putMessageBitIntoPixel, range.first, range.second);
    }

public:
    ImageEncryptor(const std::string & imagePath, const std::string & pathToWrite);
    ~ImageEncryptor();

    void encryptTest(const std::string & message);
    void encryptData(const std::string & message);
};

}

#endif