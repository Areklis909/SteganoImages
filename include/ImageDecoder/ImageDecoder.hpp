#ifndef IMAGE_DECODER_HPP
#define IMAGE_DECODER_HPP

#include <BitwiseOperations/BitwiseOperations.hpp>
#include <ConstData/ConstData.hpp>
#include <ImageHandler/ImageHandlerInterface.hpp>
#include <ImageDecoder/ImageDecoderInterface.hpp>
#include <memory>

namespace NsImageDecoder {

class ImageDecoder : public NsBitwiseOperations::BitwiseOperations, ImageDecoderInterface {

  std::unique_ptr<NsImageHandler::ImageHandlerInterface> handler;

  size_t getMessageSize() override;
  std::string getMessage(const size_t messageSize) override;
  bool findSteganoMarker() override;
  // std::string getContent(const size_t start, const size_t messageSize);
public:
  ImageDecoder(std::unique_ptr<NsImageHandler::ImageHandlerInterface> hdl);

  std::string readMessage();
};

} // namespace NsImageDecoder

#endif