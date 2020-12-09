#ifndef IMAGE_ENCRYPTOR_MOCK
#define IMAGE_ENCRYPTOR_MOCK

#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include <ImageEncryptor/ImageEncryptorInterface.hpp>
#include <ImageHandler/ImageHandlerInterface.hpp>
#include <memory>
#include <string>
#include <utility>

namespace NsTest {

class ImageEncryptorMock : public NsImageEncryptor::ImageEncryptorInterface {

public:

    ImageEncryptorMock(std::unique_ptr<NsImageHandler::ImageHandlerInterface> hdl) : NsImageEncryptor::ImageEncryptorInterface(std::move(hdl)) {};

    MOCK_METHOD(void, encryptData, (const std::string &), (override));
};


}

#endif