#include <App/App.hpp>


int main(int argc, const char **argv) {

  NsApp::App app;
  return app.run(argc, argv);
  // try {
  //   CommandLineParser parser;
  //   parser.parseCommandLine(argc, argv);
  //   const std::string input{parser.getInputImagePath()};
  //   if (parser.getProcessingMode() == ProcessingMode::fromString("encoding")) {
  //     const std::string output{parser.getOutputImagePath()};
  //     // ImageEncryptorFactory factory;

  //     // NsImageEncryptor::ImageEncryptor encryptor(input, output);
  //     // encryptor.encryptData(parser.getMessage());
  //   } else if (parser.getProcessingMode() ==
  //              ProcessingMode::fromString("decoding")) {
  //     NsImageDecoder::ImageDecoder decoder(input);
  //     NsResultHandler::ResultHandler handler(
  //         decoder.readMessage(), parser.getOutputMode(),
  //         std::optional<std::string>(parser.getMessageFilePath()));
  //   } else {
  //     std::cout << "Wrong command line options!\n";
  //   }
  // } catch (...) {
  //   return lippincott();
  // }
}