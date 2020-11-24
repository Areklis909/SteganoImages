#ifndef IMAGE_HANDLER_CPP
#define IMAGE_HANDLER_CPP

#include <ConstData/ConstData.hpp>
#include <ImageHandler/ImageHandler.hpp>
#include <MessageTooBigException/MessageTooBigException.hpp>

namespace NsImageHandler {

ImageHandler::ImageHandler(const std::string &imagePath,
                           const std::string &pathToWrite)
    : image(cv::imread(imagePath)), pathToWrite(pathToWrite) {
  checkImageProperties(imagePath);
}

ImageHandler::ImageHandler(const std::string &imagePath)
    : image(cv::imread(imagePath)), pathToWrite("") {
  checkImageProperties(imagePath);
}

void ImageHandler::checkImageProperties(const std::string &imagePath) {
  if (image.empty() || image.depth() != CV_8U) {
    throw std::runtime_error("Failed to open requested image: " + imagePath);
  }
  numOfPixels = channels() * rows() * cols();
}

ImageHandler::~ImageHandler() {
  if (pathToWrite.empty() == false) {
    cv::imwrite(pathToWrite, image);
  }
}

int ImageHandler::channels() const { return image.channels(); }

int ImageHandler::depth() const { return image.depth(); }

int ImageHandler::rows() const { return image.rows; }

int ImageHandler::cols() const { return image.cols; }

const std::string &ImageHandler::getSteganoMarker() const {
  return steganoMarker;
}

size_t ImageHandler::getSteganoMarkerSizeInBits() const {
  using namespace NsConstData;
  return steganoMarker.size() * bitsInByte;
}

int ImageHandler::getNumOfPixels() const { return numOfPixels; }

void ImageHandler::verifyMessageSize(const size_t messageSize,
                                     const size_t markerSize) {
  using namespace NsConstData;
  using namespace NsMessageTooBigException;
  const size_t maxSize =
      (cols() * rows()) - msgSizeMarkerSizeInBits - markerSize;
  if (messageSize > maxSize) {
    throw MessageTooBigException();
  }
}

void ImageHandler::applyToEveryPixelInRangeRaw(
    std::unique_ptr<NsPixelStrategy::PixelStrategy> op, const int start,
    const int end) {

  if (start > end) {
    throw std::runtime_error("Start > end!");
  }

  const int msgSize = end - start;
  int numberOfRows{cols()}, numberOfCols{rows()};
  if (image.isContinuous() == true) {
    numberOfCols *= numberOfRows;
    numberOfRows = 1;
  }
  numberOfCols *= channels();

  const int startRow = start / numberOfCols;
  const int startCol = start % numberOfCols;
  const int msgNumOfRows = msgSize / numberOfCols;
  const int restCols = msgSize % numberOfCols;

  unsigned char *ptr;
  for (int i = startRow; i <= startRow + msgNumOfRows; ++i) {
    ptr = image.ptr<unsigned char>(i);
    const int jMax = (i == msgNumOfRows + startRow) ? restCols : numberOfCols;
    const int jStart = (i == startRow) ? startCol : 0;
    for (int j = jStart; j < jStart + jMax; ++j) {
      ptr[j] = op->pixelOperation(ptr[j]);
    }
  }
}

} // namespace NsImageHandler

#endif
