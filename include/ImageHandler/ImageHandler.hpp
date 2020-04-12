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

    cv::Mat & getChannel(const int channelNumber);
public:

    ImageHandler(const std::string & imagePath, const std::string & pathToWrite);
    ~ImageHandler();

    int channels() const;
    int depth() const;
    int rows() const;
    int cols() const;
    int getNumOfPixels() const;

    cv::Mat & getRedChannel();
    cv::Mat & getGreenChannel();
    cv::Mat & getBlueChannel();

    template<typename Procedure>
    void applyToEveryPixel(Procedure procedure) {
    
        const int numberOfRows = (image.isContinuous() == true) ? 1 : rows();
        const int numberOfCols = (image.isContinuous() == true) ? cols() * numberOfRows : cols();

        unsigned char * ptr;
        for(int i = 0; i < numberOfRows; ++i) {

            ptr = image.ptr<unsigned char>(i);
            for(int j = 0; j < numberOfCols; ++j) {
                procedure(ptr[j]);
            }
        }
    }

};



}


#endif