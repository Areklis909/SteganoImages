#include "ImageHandlerMock.hpp"
#include <ImageEncryptor/ImageEncryptorFactory.hpp>
#include <ImageEncryptor/SingleImageEncryptor.hpp>
#include "gtest/gtest.h"
#include <utility>

using NsTest::ImageHandlerMock;
using ::testing::Return;
using ::testing::ReturnRef;

TEST(ImageHandlerTest, EncryptionIntegrationTest) {

    std::string marker = "SteganoMarker";
    std::string msg = "DummyMessage";
    auto hdl = std::make_unique<ImageHandlerMock>();

    EXPECT_CALL(*hdl, getSteganoMarker)
        .Times(1)
        .WillOnce(ReturnRef(marker));
    EXPECT_CALL(*hdl, getNumOfPixels)
        .Times(3)
        .WillRepeatedly(Return(1000));
    EXPECT_CALL(*hdl, applyToEveryPixelInRangeRaw)
        .Times(3);
    EXPECT_CALL(*hdl, getSteganoMarkerSizeInBits)
        .Times(2)
        .WillRepeatedly(Return(64));

    NsImageEncryptor::ImageEncryptorFactory factory;
    auto encryptor = factory.get("SINGLE", std::move(hdl));
    encryptor->encrypt(msg);
}