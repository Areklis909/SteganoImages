#ifndef IMAGE_HANDLER_INTERFACE_HPP
#define IMAGE_HANDLER_INTERFACE_HPP

#include <string>
#include <memory>
#include <PixelStrategy/PixelStrategy.hpp>

namespace NsImageHandler {

class ImageHandlerInterface {

public:
    ImageHandlerInterface() = default;
    virtual ~ImageHandlerInterface() = default;

    virtual int channels() const = 0;
    virtual int depth() const = 0;
    virtual int rows() const = 0;
    virtual int cols() const = 0;
    virtual int getNumOfPixels() const = 0;
    virtual void verifyMessageSize(const size_t messageSize, const size_t markerSize) = 0;
    virtual void applyToEveryPixelInRangeRaw(std::shared_ptr<NsPixelStrategy::PixelStrategy> op, const int start, const int end) = 0;
};


}

#endif