#include <ImageEncryptor/ImageEncryptor.hpp>
#include <ImageDecoder/ImageDecoder.hpp>

int main() {
    const std::string inputPath {"/home/alis/SteganoImages/src/obraz.PNG"};
    const std::string outputPath {"/home/alis/SteganoImages/src/obraz2.PNG"};
    NsImageEncryptor::ImageEncryptor encryptor(inputPath, outputPath);
    encryptor.encryptData("Arek");
    NsImageDecoder::ImageDecoder decoder(outputPath);
    std::cout << decoder.readMessage();
    return 0;
}