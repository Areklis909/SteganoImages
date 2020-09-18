#include <CommandLineParser/CommandLineParser.hpp>
#include <ImageDecoder/ImageDecoder.hpp>
#include <ImageEncryptor/ImageEncryptor.hpp>
#include <MessageTooBigException/MessageTooBigException.hpp>
#include <NotSteganoException/NotSteganoException.hpp>
#include <ResultHandler/ResultHandler.hpp>

enum ErrorCodes {
  NotStegano = 4,
  MessageTooBig = 5,
  General = 6
};

int lippincott() {
  try {
    throw;
  } catch (NsNotSteganoException::NotSteganoException &nse) {
    std::cout << nse.what();
    return ErrorCodes::NotStegano;
  } catch (NsMessageTooBigException::MessageTooBigException &mtbe) {
    std::cout << mtbe.what();
    return ErrorCodes::MessageTooBig;
  } catch (std::runtime_error &re) {
    std::cout << re.what();
    return ErrorCodes::General;
  } catch (std::exception &e) {
    std::cout << "Unknown exception occurred: " << e.what() << '\n';
    return ErrorCodes::General;
  }
}

int main(int argc, char **argv) {
  using NsSteganoCommandLineParser::CommandLineParser;
  using namespace NsProcessingMode;

  try {
    CommandLineParser parser;
    parser.parseCommandLine(argc, argv);
    const std::string input{parser.getInputImagePath()};
    if (parser.getProcessingMode() == ProcessingMode::fromString("encoding")) {
      const std::string output{parser.getOutputImagePath()};
      NsImageEncryptor::ImageEncryptor encryptor(input, output);
      encryptor.encryptData(parser.getMessage());
    } else if (parser.getProcessingMode() ==
               ProcessingMode::fromString("decoding")) {
      NsImageDecoder::ImageDecoder decoder(input);
      NsResultHandler::ResultHandler handler(
          decoder.readMessage(), parser.getOutputMode(),
          std::optional<std::string>(parser.getMessageFilePath()));
    } else {
      std::cout << "Wrong command line options!\n";
    }
  } catch (...) {
    return lippincott();
  }

  return 0;
}