#ifndef COMMAND_LINE_PARSER_CPP
#define COMMAND_LINE_PARSER_CPP

#include <CommandLineParser/CommandLineParser.hpp>

namespace NsSteganoCommandLineParser {


CommandLineParser::CommandLineParser() : optionsDescription("Allowed options") {
    // produces proxy object with overloaded operator()
    optionsDescription.add_options()
        (helpStr, "Show help message")
        (inputImageStr, po::value<std::string>(), "Path of image to process")
        (outputImageStr, po::value<std::string>(), "Processed image name")
        (messageFileStr, po::value<std::string>(), "Path to file containing a message")
        (messageStr, po::value<std::string>(), "Message supplied directly to command line")
        (modeStr, po::value<std::string>(), "ProcessingMode: [encoding|decoding]");
}

void CommandLineParser::parseCommandLine(int argc, char ** argv) {
    po::store(po::parse_command_line(argc, argv, optionsDescription), variablesMap);
    po::notify(variablesMap);
}

std::string CommandLineParser::getInputImagePath() {
    return getOption<std::string>(inputImageStr);
}

std::string CommandLineParser::getOutputImagePath() {
    return getOption<std::string>(outputImageStr);
}

std::string CommandLineParser::getMessageFilePath() {
    return getOption<std::string>(messageFileStr);
}

std::string CommandLineParser::getMessage() {
    return getOption<std::string>(messageStr);
}

NsProcessingMode::ProcessingMode CommandLineParser::getProcessingMode() {
    const std::string mode = getOption<std::string>(modeStr);
    return NsProcessingMode::ProcessingMode::fromString(mode);
}

bool CommandLineParser::isInputImagePathSet() const {
    return isOptionSet<std::string>(inputImageStr);
}

bool CommandLineParser::isOutputImagePathSet() const {
    return isOptionSet<std::string>(outputImageStr);
}

bool CommandLineParser::isMessageFilePathSet() const {
    return isOptionSet<std::string>(messageFileStr);
}

bool CommandLineParser::isMessageSet() const {
    return isOptionSet<std::string>(messageStr);
}

bool CommandLineParser::isProcessingModeSet() const {
    return isOptionSet<NsProcessingMode::ProcessingMode>(modeStr);
}


}
#endif