#ifndef IMAGE_HANDLER_HPP
#define IMAGE_HANDLER_HPP

#include <opencv2/opencv.hpp>
#include <string>
#include <vector>

namespace NsImageHandler {

class ImageHandler {

  cv::Mat image;
  const std::string pathToWrite;

  const int redChannel;
  const int greenChannel;
  const int blueChannel;

  int numOfPixels;
  std::vector<cv::Mat> splitChannels;
  const std::string steganoMarker;


  cv::Mat &getChannel(const int channelNumber);
  void checkImageProperties(const std::string &imagePath);

public:
  ImageHandler(const std::string &imagePath, const std::string &pathToWrite);
  ImageHandler(const std::string &imagePath);
  ~ImageHandler();

  int channels() const;
  int depth() const;
  int rows() const;
  int cols() const;
  int getNumOfPixels() const;
  const std::string & getSteganoMarker() const;
  size_t getSteganoMarkerSizeInBits() const;

  cv::Mat &getRedChannel();
  cv::Mat &getGreenChannel();
  cv::Mat &getBlueChannel();

  void verifyMessageSize(const size_t messageSize, const size_t markerSize);

  template <typename Procedure>
  void applyToEveryPixelGrayscale(Procedure procedure, const int start,
                                  const int end) {
    cv::MatIterator_<unsigned char> imgBegin, imgEnd;
    imgBegin = image.begin<unsigned char>() + start;
    imgEnd = imgBegin + end;

    for (; imgBegin != imgEnd; ++imgBegin) {
      procedure(*imgBegin);
    }
  }

  template <typename Procedure>
  void applyToEveryPixelColor(Procedure procedure, const int start,
                              const int end) {
    cv::MatIterator_<cv::Vec3b> imgBegin, imgEnd;
    const int subpixels = 3;

    imgBegin = image.begin<cv::Vec3b>() + start;
    imgEnd = imgBegin + end / subpixels;

    const int distance = end - start;
    const int rest = distance % subpixels;

    for (; imgBegin != imgEnd; ++imgBegin) {
      for (int i = 0; i < 3; ++i) {
        procedure((*imgBegin)[i]);
      }
    }

    for (int i = 0; i < rest; ++i) {
      procedure((*imgBegin)[i]);
    }
  }

  template <typename Procedure>
  void applyToEveryPixelInRange(Procedure procedure, const int start,
                                const int end) {

    if (start > end) {
      throw std::runtime_error("Start > end!");
    }

    const int oneChannel = 1;
    const int threeChannels = 3;

    switch (channels()) {
    case oneChannel: {
      applyToEveryPixelGrayscale(procedure, start, end);
      break;
    }
    case threeChannels: {
      applyToEveryPixelColor(procedure, start, end);
      break;
    }
    default: { throw std::runtime_error("Unsupported number of channels"); }
    }
  }

  template <typename Procedure>
  void applyToEveryPixelInRangeRaw(Procedure procedure, const int start,
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
        procedure(ptr[j]);
      }
    }
  }
};

} // namespace NsImageHandler

#endif