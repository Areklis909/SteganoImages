#ifndef IMAGE_HANDLER_CPP
#define IMAGE_HANDLER_CPP

#include <ImageHandler/ImageHandler.hpp>
#include <ConstData/ConstData.hpp>
#include <MessageTooBigException/MessageTooBigException.hpp>

namespace NsImageHandler {

ImageHandler::ImageHandler(const std::string & imagePath, const std::string & pathToWrite) :
    image(cv::imread(imagePath)),
    pathToWrite(pathToWrite),
    redChannel(2),
    greenChannel(1),
    blueChannel(0),
    steganoMarker("SteganoImages")
{
    checkImageProperties(imagePath);
}

ImageHandler::ImageHandler(const std::string & imagePath) : image(cv::imread(imagePath)),
    pathToWrite(""),
    redChannel(2),
    greenChannel(1),
    blueChannel(0),
    steganoMarker("SteganoImages")
{
    checkImageProperties(imagePath);
}

void ImageHandler::checkImageProperties(const std::string & imagePath) {
    if(image.empty() || image.depth() != CV_8U) {
        throw std::runtime_error("Failed to open requested image: " + imagePath);
    }
    numOfPixels = channels() * rows() * cols();
    std::cout << "rows: " << rows() << " cols: " << cols() << " is continuous: " << image.isContinuous() << '\n';
}

ImageHandler::~ImageHandler() {
    if(pathToWrite.empty() == false) {
        cv::imwrite(pathToWrite, image);
    }
}

int ImageHandler::channels() const {
    return image.channels();
}

int ImageHandler::depth() const {
    return image.depth();
}

int ImageHandler::rows() const {
    return image.rows;
}

int ImageHandler::cols() const {
    return image.cols;
}

const std::string & ImageHandler::getSteganoMarker() const {
    return steganoMarker;
}

size_t ImageHandler::getSteganoMarkerSizeInBits() const {
    using namespace NsConstData;
    return steganoMarker.size() * bitsInByte;
}


cv::Mat & ImageHandler::getChannel(const int channelNumber) {
    if(splitChannels.empty() == true) {
        cv::split(image, splitChannels);
    }
    return splitChannels.at(channelNumber);
}


cv::Mat & ImageHandler::getRedChannel() {
    return getChannel(redChannel);
}

cv::Mat & ImageHandler::getGreenChannel() {
    return getChannel(greenChannel);
}

cv::Mat & ImageHandler::getBlueChannel() {
    return getChannel(blueChannel);
}

int ImageHandler::getNumOfPixels() const {
    return numOfPixels;
}

void ImageHandler::verifyMessageSize(const size_t messageSize, const size_t markerSize) {
    using namespace NsConstData;
    using namespace NsMessageTooBigException;
    const size_t maxSize = (cols() * rows()) - msgSizeMarkerSizeInBits - markerSize;
    if(messageSize > maxSize) {
        throw MessageTooBigException();
    }
}

}

#endif
