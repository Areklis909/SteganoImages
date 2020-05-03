#include <ImageEncryptor/ImageEncryptor.hpp>
#include <ImageDecoder/ImageDecoder.hpp>
#include <CommandLineParser/CommandLineParser.hpp>

int main(int argc, char ** argv) {
    NsSteganoCommandLineParser::CommandLineParser parser;
    parser.parseCommandLine(argc, argv);

    const std::string inputPath {parser.getInputImagePath()};
    const std::string outputPath {parser.getOutputImagePath()};
    {
        NsImageEncryptor::ImageEncryptor encryptor(inputPath, outputPath);
        encryptor.encryptData("Przykladowa wiadomosc");
    }
    
    NsImageDecoder::ImageDecoder decoder(outputPath);
    const std::string output = decoder.readMessage();
    std::cout << output << '\n';
    return 0;
}