#ifndef IMAGE_DECODER_HPP
#define IMAGE_DECODER_HPP

#include <BitwiseOperations/BitwiseOperations.hpp>
#include <ConstData/ConstData.hpp>
#include <ImageHandler/ImageHandler.hpp>

namespace NsImageDecoder {

class ImageDecoder : public NsBitwiseOperations::BitwiseOperations {

  NsImageHandler::ImageHandler image;

  size_t getMessageSize();
  std::string getMessage(const size_t startPoint);

public:
  ImageDecoder(const std::string &imagePath);
  ~ImageDecoder();

  std::string readMessage();
};

} // namespace NsImageDecoder

#endif