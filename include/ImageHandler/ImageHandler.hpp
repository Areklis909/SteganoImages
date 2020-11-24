#ifndef IMAGE_HANDLER_HPP
#define IMAGE_HANDLER_HPP

#include <opencv2/opencv.hpp>
#include <string>
#include <vector>
#include "ImageHandlerInterface.hpp"

namespace NsImageHandler {

class ImageHandler : public ImageHandlerInterface {

  cv::Mat image;
  int numOfPixels;
  const std::string pathToWrite;
  const std::string steganoMarker = "SteganoImages";

  void checkImageProperties(const std::string &imagePath);
public:
  ImageHandler(const std::string &imagePath, const std::string &pathToWrite);
  ImageHandler(const std::string &imagePath);
  ~ImageHandler();

  int channels() const override;
  int depth() const override;
  int rows() const override;
  int cols() const override;
  int getNumOfPixels() const override;
  const std::string & getSteganoMarker() const override;
  size_t getSteganoMarkerSizeInBits() const override;
  void verifyMessageSize(const size_t messageSize, const size_t markerSize) override;
  void applyToEveryPixelInRangeRaw(std::unique_ptr<NsPixelStrategy::PixelStrategy> op, const int start, const int end) override;
};

} // namespace NsImageHandler

#endif