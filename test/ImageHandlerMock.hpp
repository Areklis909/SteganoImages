#ifndef IMAGE_HANDLER_MOCK
#define IMAGE_HANDLER_MOCK

#include "gmock/gmock.h"
#include <ImageHandler/ImageHandlerInterface.hpp>
#include <PixelStrategy/PixelStrategy.hpp>
#include <memory>
#include <string>

namespace NsTest {

class ImageHandlerMock : public NsImageHandler::ImageHandlerInterface {

public:
    MOCK_METHOD(int, channels, (), (const, override));
    MOCK_METHOD(int, depth, (), (const, override));
    MOCK_METHOD(int, rows, (), (const, override));
    MOCK_METHOD(int, cols, (), (const, override));
    MOCK_METHOD(int, getNumOfPixels, (), (const, override));
    MOCK_METHOD(void, verifyMessageSize, (const size_t, const size_t), (override));
    MOCK_METHOD(void, applyToEveryPixelInRangeRaw, (std::shared_ptr<NsPixelStrategy::PixelStrategy>, const int, const int), (override));
};


}

#endif