#include <string>
#include <memory>
#include "ImageEncryptorFactory.hpp"

namespace NsImageEncryptor {

class ImageEncryptorManagerInterface {

    size_t msgLengthLimit();
public:
    ImageEncryptorManagerInterface() = default;
    ~ImageEncryptorManagerInterface() = default;

    virtual void doWork(const std::string &msg) = 0;
    virtual size_t getMsgLengthLimit() = 0;
protected:
    std::unique_ptr<ImageEncryptorFactoryInterface> factory;
};


}