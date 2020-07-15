#ifndef RESULT_HANDLER_CPP
#define RESULT_HANDLER_CPP

#include <ResultHandler/ResultHandler.hpp>
#include <iostream>

namespace NsResultHandler {

ResultHandler::ResultHandler(const std::string &result,
                             NsOutputMode::OutputMode mode,
                             std::optional<std::string> filePath) {

  using namespace NsOutputMode;
  using namespace NsMessageSaver;
  if (mode == OutputMode::fromString(OutputMode::fileStr)) {
    MessageSaver msgSaver(*filePath);
    msgSaver.saveMessage(result);
  } else {
    std::cout << result << '\n';
  }
}

}


#endif