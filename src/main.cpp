#include <CommandLineParser/CommandLineParser.hpp>
#include <ImageDecoder/ImageDecoder.hpp>
#include <ImageEncryptor/ImageEncryptor.hpp>
#include <MessageTooBigException/MessageTooBigException.hpp>
#include <NotSteganoException/NotSteganoException.hpp>

void lippincott() {
  try {
    throw;
  } catch (NsNotSteganoException::NotSteganoException &nse) {
    std::clog << nse.what();
  } catch (NsMessageTooBigException::MessageTooBigException &mtbe) {
    std::clog << mtbe.what();
  } catch (std::runtime_error &re) {
    std::clog << re.what();
  } catch(std::exception & e) {
    std::cerr << "Unknown exception occurred: " << e.what() << '\n';
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
      const std::string text = decoder.readMessage();
      std::cout << text << '\n';
    } else {
      std::cout << "Wrong command line options!\n";
    }
  } catch (...) {
    lippincott();
  }

  return 0;
}