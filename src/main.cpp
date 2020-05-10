#include <ImageEncryptor/ImageEncryptor.hpp>
#include <ImageDecoder/ImageDecoder.hpp>
#include <CommandLineParser/CommandLineParser.hpp>

int main(int argc, char ** argv) {
    using NsSteganoCommandLineParser::CommandLineParser;
    using namespace NsProcessingMode;

    CommandLineParser parser;
    parser.parseCommandLine(argc, argv);

    const std::string input {parser.getInputImagePath()};
    if(parser.getProcessingMode() == ProcessingMode::fromString("encoding")) {
        const std::string output {parser.getOutputImagePath()};
        NsImageEncryptor::ImageEncryptor encryptor(input, output);
        encryptor.encryptData(parser.getMessage());
    } else if(parser.getProcessingMode() == ProcessingMode::fromString("decoding")) {
        NsImageDecoder::ImageDecoder decoder(input);
        const std::string text = decoder.readMessage();
        std::cout << text << '\n';
    } else {
        std::cout << "Wrong command line options!\n";
    }

    return 0;
}