#include "gtest/gtest.h"
#include <ImageEncryptor/SingleImageEncryptor.hpp>
#include "ImageEncryptorMock.hpp"
#include "ImageHandlerMock.hpp"
#include "WriteStrategyMock.hpp"
#include <memory>
#include <string>
#include <utility>


using ::testing::Return;
using NsTest::ImageHandlerMock;
using NsTest::ImageEncryptorMock;
using NsTest::WriteStrategyMock;

TEST(ImageEncryptorTest, shouldEncryptMarkerSizeAndMsg) {

    const std::string msg {"DummyMessage"};
    auto hdl = std::make_unique<ImageHandlerMock>();

    EXPECT_CALL(*hdl, applyToEveryPixelInRangeRaw)
        .Times(2);
    EXPECT_CALL(*hdl, getNumOfPixels)
        .Times(2)
        .WillRepeatedly(Return(1000));

    auto enc = std::make_unique<ImageEncryptorMock>(std::move(hdl));
    enc->setStrategy(std::make_shared<WriteStrategyMock>());

    EXPECT_CALL(*enc, encryptData)
        .Times(1);
        
    enc->encrypt(msg);
}