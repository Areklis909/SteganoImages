#ifndef IMAGE_ENCRYPTOR_HPP
#define IMAGE_ENCRYPTOR_HPP

#include <type_traits>
#include <ConstData/ConstData.hpp>
#include <BitwiseOperations/BitwiseOperations.hpp> 
#include <ImageHandler/ImageHandler.hpp>
#include <ParallelEncoder/TaskDetail.hpp>
#include <ParallelEncoder/ParallelEncoder.hpp>

namespace NsImageEncryptor {

class ImageEncryptor : public NsBitwiseOperations::BitwiseOperations {

    NsImageHandler::ImageHandler imageHandler;
    const size_t messageLengthThreshold;
    const size_t noThreads;

    NsRange::Range getMessageRange(const std::string & message, const int start);
    void encryptMulti(const NsTaskDetail::TaskDetail taskDetail);
    void encryptSingle(const std::string & message, const int startPoint);
    std::vector<NsRange::Range> divideIntoRanges(const std::string & message, const int start);
    std::vector<std::string_view> divideIntoSubmessages(const std::string & message, const std::vector<NsRange::Range> & ranges);
    std::vector<NsTaskDetail::TaskDetail> getTaskDetails(const std::string & message, const int start);


    template<typename T>
    NsRange::Range getMessageRange(T message, const int start) {
        using NsRange::Range;
        using namespace NsConstData;

        const int msgSizeInBits = sizeof(message) * bitsInByte;
        const int allPixels = imageHandler.getNumOfPixels();
        if(msgSizeInBits > allPixels) {
            throw std::runtime_error("Message is too big!");
        }
        return Range(start, start + msgSizeInBits);
    }

    template<typename T>
    char * toBytes(T data) {
        T * ptr = static_cast<T *>(&data);
        void * dataBuf = static_cast<void *>(ptr);
        return static_cast<char *>(dataBuf);
    }

    void encodeMessageSize(const size_t message, const int startPoint) {
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
        imageHandler.applyToEveryPixelInRangeRaw(putMessageBitIntoPixel, range.start(), range.end());
    }

public:
    ImageEncryptor(const std::string & imagePath, const std::string & pathToWrite);
    ~ImageEncryptor();

    void encryptData(const std::string & message);
};

}

#endif