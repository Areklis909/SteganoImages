#include <string>
#include <memory>
#include <ImageEncryptor/ImageEncryptorInterface.hpp>
#include "ImageEncryptorManagerInterface.hpp"

namespace NsImageEncryptor {

class ImageEncryptorManager : public ImageEncryptorManagerInterface{

    std::unique_ptr<ImageEncryptorInterface> encryptor;
    std::string input;
    std::string output;
public:
    ImageEncryptorManager() = default;
    ImageEncryptorManager(const std::string & in, const std::string & out);
    ~ImageEncryptorManager() = default;

    void doWork(const std::string &msg) override;
    size_t getMsgLengthLimit() override;
    void setEncryptor(std::unique_ptr<ImageEncryptorInterface> enc);
    void setInput(const std::string & in);
    void setOutput(const std::string & out);
};


}