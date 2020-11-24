#ifndef PIXEL_STRATEGY_HPP
#define PIXEL_STRATEGY_HPP

namespace NsPixelStrategy {

class PixelStrategy {
public:
    PixelStrategy() = default;
    ~PixelStrategy() = default;
    virtual char pixelOperation(char byte) = 0;
};


}

#endif