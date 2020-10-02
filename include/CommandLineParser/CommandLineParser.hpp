#ifndef COMMAND_LINE_PARSER_HPP
#define COMMAND_LINE_PARSER_HPP

#include <ProcessingMode/ProcessingMode.hpp>
#include <OutputMode/OutputMode.hpp>
#include <boost/program_options.hpp>
#include <string>


namespace NsSteganoCommandLineParser {

namespace po = boost::program_options;

class CommandLineParser {
  po::options_description optionsDescription;
  po::variables_map variablesMap;

  const char *helpStr = "help";
  const char *inputImageStr = "input";
  const char *outputImageStr = "output";
  const char *messageFileStr = "message-file";
  const char *messageStr = "message";
  const char *modeStr = "mode";

  template <typename T> T getOption(const std::string &optionName) {
    if(variablesMap.count(optionName) == 0) {
      return T{};
    }
    return variablesMap.at(optionName.data()).as<T>();
  }

  template <typename T> bool isOptionSet(const std::string &optionName) const {
    if (variablesMap.count(optionName)) {
      return true;
    }
    return false;
  }

public:
  CommandLineParser();
  void parseCommandLine(int argc, char **argv);

  std::string getInputImagePath();
  std::string getOutputImagePath();
  std::string getMessageFilePath();
  std::string getMessage();
  NsProcessingMode::ProcessingMode getProcessingMode();
  NsOutputMode::OutputMode getOutputMode();

  bool isInputImagePathSet() const;
  bool isOutputImagePathSet() const;
  bool isMessageFilePathSet() const;
  bool isMessageSet() const;
  bool isProcessingModeSet() const;
};

} // namespace NsSteganoCommandLineParser

#endif
