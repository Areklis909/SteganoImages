#include "gtest/gtest.h"
#include <ImageEncryptor/SingleImageEncryptor.hpp>
#include "ImageEncryptorMock.hpp"
#include "ImageHandlerMock.hpp"

using ::testing::Return;
using ::testing::ReturnRef;
using NsTest::ImageHandlerMock;
using NsTest::ImageEncryptorMock;
using NsImageEncryptor::SingleImageEncryptor;

TEST(ImageEncryptorTest, shouldEncryptMarkerSizeAndMsg) {

    const std::string marker {"SteganoImages"};
    const std::string msg {"DummyMessage"};
    auto hdl = std::make_unique<ImageHandlerMock>();

    EXPECT_CALL(*hdl, getSteganoMarker)
        .Times(1)
        .WillOnce(ReturnRef(marker));
    EXPECT_CALL(*hdl, getNumOfPixels)
        .Times(2)
        .WillRepeatedly(Return(1000));
    EXPECT_CALL(*hdl, applyToEveryPixelInRangeRaw)
        .Times(2);
    EXPECT_CALL(*hdl, getSteganoMarkerSizeInBits)
        .Times(1)
        .WillRepeatedly(Return(64));

    auto enc = std::make_unique<ImageEncryptorMock>(std::move(hdl));

    EXPECT_CALL(*enc, encryptData)
        .Times(1);
        
    enc->encrypt(msg);
}