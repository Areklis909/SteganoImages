#ifndef IMAGE_DECODER_HPP
#define IMAGE_DECODER_HPP

#include <ImageHandler/ImageHandler.hpp>
#include <ConstData/ConstData.hpp>

namespace NsImageDecoder {

class ImageDecoder {

    NsImageHandler::ImageHandler image;

    size_t getMessageSize();
    std::string getMessage(const size_t startPoint);
public:
    ImageDecoder(const std::string & imagePath);
    ~ImageDecoder();

    std::string readMessage();
};


}


#endif