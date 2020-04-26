#ifndef IMAGE_HANDLER_CPP
#define IMAGE_HANDLER_CPP

#include <ImageHandler/ImageHandler.hpp>
#include <exception>

namespace NsImageHandler {

ImageHandler::ImageHandler(const std::string & imagePath, const std::string & pathToWrite) :
    image(cv::imread(imagePath)),
    pathToWrite(pathToWrite),
    redChannel(2),
    greenChannel(1),
    blueChannel(0)
{
    checkImageProperties(imagePath);
}

ImageHandler::ImageHandler(const std::string & imagePath) : image(cv::imread(imagePath)),
    pathToWrite(""),
    redChannel(2),
    greenChannel(1),
    blueChannel(0)
{
    checkImageProperties(imagePath);
}

void ImageHandler::checkImageProperties(const std::string & imagePath) {
    if(image.empty() || image.depth() != CV_8U) {
        throw std::runtime_error("Failed to open requested image: " + imagePath);
    }
    numOfPixels = channels() * rows() * cols();
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

}

#endif
