#ifndef IMAGE_DECODER_INTERFACE_HPP
#define IMAGE_DECODER_INTERFACE_HPP

#include <string>
#include <ImageHandler/ImageHandlerInterface.hpp>
#include <ConstData/ConstData.hpp>

namespace NsImageDecoder {

class ImageDecoderInterface {

public:
  ImageDecoderInterface() = default;
  virtual ~ImageDecoderInterface() = default;
  
  std::string readMessage();
private:
  virtual bool findSteganoMarker() = 0;
  virtual size_t getMessageSize() = 0;
  virtual std::string getMessage(const size_t messageSize) = 0;
};


}

#endif