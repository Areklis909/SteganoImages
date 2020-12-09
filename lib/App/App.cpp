#include <App/App.hpp>
#include <CommandLineParser/CommandLineParser.hpp>
#include <ImageDecoder/ImageDecoder.hpp>
#include <ImageEncryptor/ImageEncryptorManager.hpp>
#include <MessageTooBigException/MessageTooBigException.hpp>
#include <NotSteganoException/NotSteganoException.hpp>
#include <ImageHandler/ImageHandler.hpp>
#include <iostream>

namespace NsApp {

int App::lippincott() {
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

void App::_run(int argc, const char **argv) {

  using NsImageHandler::ImageHandler;
  using NsProcessingMode::ProcessingMode;
  using NsSteganoCommandLineParser::CommandLineParser;
  using namespace NsImageEncryptor;

  CommandLineParser parser;
  parser.parseCommandLine(argc, argv);
  const std::string input{parser.getInputImagePath()};
  if (parser.getProcessingMode() == ProcessingMode::fromString("encoding")) {
    const std::string output{parser.getOutputImagePath()};
    ImageEncryptorManager manago(input, output);
    manago.doWork(parser.getMessage());
  } else {
  }
}

int App::run(int argc, const char **argv) {
  try {
    _run(argc, argv);
  } catch (...) {
    return lippincott();
  }
  return 0;
}

} // namespace NsApp