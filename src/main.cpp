#include <ImageEncryptor/ImageEncryptor.hpp>
#include <ImageDecoder/ImageDecoder.hpp>

int main() {
    const std::string inputPath {"/home/alis/SteganoImages/src/obraz.PNG"};
    const std::string outputPath {"/home/alis/SteganoImages/src/obraz2.PNG"};
    {
        NsImageEncryptor::ImageEncryptor encryptor(inputPath, outputPath);
        encryptor.encryptData("Przykladowa wiadomosc");
    }
    
    NsImageDecoder::ImageDecoder decoder(outputPath);
    const std::string output = decoder.readMessage();
    std::cout << output << '\n';
    return 0;
}